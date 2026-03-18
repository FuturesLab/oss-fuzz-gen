#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>
#include <string.h>

int LLVMFuzzerTestOneInput_103(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the function parameters
    hid_t loc_id = H5I_INVALID_HID; // Invalid ID to start with
    const char *name = "test_link"; // Example link name
    size_t size_buf = 256; // Buffer size
    char linkval[256]; // Buffer to hold the link value

    // Ensure data is not NULL and size is sufficient
    if (data == NULL || size == 0) {
        return 0;
    }

    // Create a dummy HDF5 file and a group to use for testing
    hid_t file_id = H5Fcreate("testfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id >= 0) {
        loc_id = H5Gcreate2(file_id, "/testgroup", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        if (loc_id >= 0) {
            // Create a link in the group
            H5Lcreate_soft("/testgroup", loc_id, name, H5P_DEFAULT, H5P_DEFAULT);

            // Call the function-under-test
            herr_t status = H5Gget_linkval(loc_id, name, size_buf, linkval);

            // Close the group
            H5Gclose(loc_id);
        }
        // Close the file
        H5Fclose(file_id);
    }

    return 0;
}