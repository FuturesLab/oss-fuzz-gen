#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_244(const uint8_t *data, size_t size) {
    hid_t file_id, dataset_id;
    herr_t status;
    const char *file_name = "fuzz_test_file.h5";
    const char *dataset_name = "fuzz_dataset";

    // Create a new HDF5 file using default properties.
    file_id = H5Fcreate(file_name, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    // Create a simple dataspace with one element.
    hsize_t dims[1] = {1};
    hid_t dataspace_id = H5Screate_simple(1, dims, NULL);
    if (dataspace_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Create a dataset in the file.
    dataset_id = H5Dcreate2(file_id, dataset_name, H5T_NATIVE_INT, dataspace_id, 
                            H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dataset_id < 0) {
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        return 0;
    }

    // Close the dataspace.
    H5Sclose(dataspace_id);

    // Fuzz the function-under-test: H5Dclose
    status = H5Dclose(dataset_id);

    // Clean up: Close the file.
    H5Fclose(file_id);

    return 0;
}