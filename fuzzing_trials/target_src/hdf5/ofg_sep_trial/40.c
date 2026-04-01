#include <stddef.h>
#include <stdint.h>
#include <hdf5.h>

// Define a simple iterator function
herr_t iterate_callback(hid_t group, const char *name, const H5L_info_t *info, void *op_data) {
    // Simple operation, just return success
    return 0;
}

int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for a meaningful test
    if (size < 1) {
        return 0;
    }

    // Initialize HDF5 library
    H5open();

    // Create a new file using default properties.
    hid_t file_id = H5Fcreate("fuzz_test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    // Create a group in the file.
    hid_t group_id = H5Gcreate2(file_id, "/TestGroup", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    // Prepare the parameters for H5Literate
    hsize_t idx = 0;
    void *op_data = NULL; // No operation data needed for this simple example

    // Call the function-under-test
    H5Literate(group_id, H5_INDEX_NAME, H5_ITER_INC, &idx, iterate_callback, op_data);

    // Close the group and file
    H5Gclose(group_id);
    H5Fclose(file_id);

    // Close HDF5 library
    H5close();

    return 0;
}