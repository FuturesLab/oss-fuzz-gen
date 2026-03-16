#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_135(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    hid_t dataset_id = H5I_INVALID_HID;
    hid_t type_id = H5T_NATIVE_INT;
    hid_t space_id = H5S_SIMPLE;
    hsize_t buf_size = 0;

    // Ensure the data size is sufficient for creating a dataset
    if (size < sizeof(int)) {
        return 0;
    }

    // Create a simple dataspace
    hsize_t dims[1] = { size / sizeof(int) };
    space_id = H5Screate_simple(1, dims, NULL);
    if (space_id < 0) {
        return 0;
    }

    // Create a dataset in memory
    dataset_id = H5Dcreate2(H5P_DEFAULT, "fuzz_dataset", type_id, space_id, 
                            H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dataset_id < 0) {
        H5Sclose(space_id);
        return 0;
    }

    // Call the function under test
    herr_t status = H5Dvlen_get_buf_size(dataset_id, type_id, space_id, &buf_size);

    // Clean up resources
    H5Dclose(dataset_id);
    H5Sclose(space_id);

    return 0;
}