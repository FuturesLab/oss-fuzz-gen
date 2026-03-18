#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_78(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t dataset_id = H5I_INVALID_HID;
    hsize_t dims[2] = {1, 1};  // Default dimensions

    // Ensure the size is sufficient to extract necessary data
    if (size >= sizeof(hsize_t) * 2) {
        // Extract dimensions from the data
        dims[0] = *((const hsize_t *)data);
        dims[1] = *((const hsize_t *)(data + sizeof(hsize_t)));
    }

    // Create a simple dataspace
    hid_t space_id = H5Screate_simple(2, dims, NULL);
    if (space_id < 0) {
        return 0;  // Failed to create dataspace
    }

    // Create a dataset
    hid_t file_id = H5Fcreate("tempfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        H5Sclose(space_id);
        return 0;  // Failed to create file
    }

    dataset_id = H5Dcreate2(file_id, "dataset", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dataset_id < 0) {
        H5Fclose(file_id);
        H5Sclose(space_id);
        return 0;  // Failed to create dataset
    }

    // Call the function-under-test
    herr_t status = H5Dset_extent(dataset_id, dims);

    // Clean up resources
    H5Dclose(dataset_id);
    H5Fclose(file_id);
    H5Sclose(space_id);

    return 0;
}