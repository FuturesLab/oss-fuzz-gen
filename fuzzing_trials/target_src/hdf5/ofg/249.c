#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_249(const uint8_t *data, size_t size) {
    // Initialize HDF5 library
    H5open();

    // Create a file to work with
    hid_t file_id = H5Fcreate("fuzz_test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Determine the number of integers we can write from the input data
    size_t num_ints = size / sizeof(int);
    if (num_ints == 0) {
        H5Fclose(file_id);
        H5close();
        return 0;
    }

    // Create a dataspace
    hsize_t dims[1] = {num_ints};
    hid_t dataspace_id = H5Screate_simple(1, dims, NULL);
    if (dataspace_id < 0) {
        H5Fclose(file_id);
        H5close();
        return 0;
    }

    // Create a dataset
    hid_t dataset_id = H5Dcreate2(file_id, "dataset", H5T_NATIVE_INT, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dataset_id < 0) {
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        H5close();
        return 0;
    }

    // Use the input data to write to the dataset
    herr_t write_status = H5Dwrite(dataset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
    if (write_status < 0) {
        H5Dclose(dataset_id);
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        H5close();
        return 0;
    }

    // Call the function-under-test
    herr_t status = H5Drefresh(dataset_id);

    // Clean up
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);

    // Close HDF5 library
    H5close();

    return 0;
}