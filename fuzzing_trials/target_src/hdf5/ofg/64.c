#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include this for memcpy
#include <hdf5.h>

int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    // Initialize variables
    hid_t loc_id = H5I_INVALID_HID;
    hid_t child_id = H5I_INVALID_HID;
    hid_t plist_id = H5P_DEFAULT;
    char mount_name[256];

    // Ensure data is not empty and size is sufficient
    if (size < 1) {
        return 0;
    }

    // Create a valid file to serve as the location and child
    loc_id = H5Fcreate("parent.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    child_id = H5Fcreate("child.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    // Ensure the files were created successfully
    if (loc_id < 0 || child_id < 0) {
        goto cleanup;
    }

    // Copy data to mount_name ensuring it's null-terminated
    size_t copy_size = (size < sizeof(mount_name) - 1) ? size : sizeof(mount_name) - 1;
    memcpy(mount_name, data, copy_size);
    mount_name[copy_size] = '\0';

    // Call the function-under-test
    herr_t result = H5Fmount(loc_id, mount_name, child_id, plist_id);

cleanup:
    // Close the HDF5 files
    if (loc_id >= 0) {
        H5Fclose(loc_id);
    }
    if (child_id >= 0) {
        H5Fclose(child_id);
    }

    return 0;
}