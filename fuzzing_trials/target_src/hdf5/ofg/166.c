#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_166(const uint8_t *data, size_t size) {
    // Initialize HDF5 library
    H5open();

    // Create a temporary file to work with
    hid_t file_id = H5Fcreate("tempfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0; // Failed to create file, exit early
    }

    // Create a dataspace
    hsize_t dims[1] = {10};
    hid_t dataspace_id = H5Screate_simple(1, dims, NULL);
    if (dataspace_id < 0) {
        H5Fclose(file_id);
        return 0; // Failed to create dataspace, exit early
    }

    // Create a dataset
    hid_t dataset_id = H5Dcreate2(file_id, "dataset", H5T_NATIVE_INT, dataspace_id,
                                  H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dataset_id < 0) {
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        return 0; // Failed to create dataset, exit early
    }

    // Use the input data to write to the dataset if the size is sufficient
    if (size >= 10 * sizeof(int)) {
        herr_t write_status = H5Dwrite(dataset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
        if (write_status < 0) {
            H5Dclose(dataset_id);
            H5Sclose(dataspace_id);
            H5Fclose(file_id);
            H5close();
            return 0; // Failed to write data, exit early
        }
    }

    // Call the function-under-test
    herr_t status = H5Dformat_convert(dataset_id);

    // Clean up resources
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);

    // Close HDF5 library
    H5close();

    return 0;
}