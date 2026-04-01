#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
    // Initialize variables for H5Gunlink parameters
    hid_t group_id = H5I_INVALID_HID;  // Invalid ID to start with
    char *name = NULL;

    // Ensure size is sufficient to create a valid name string
    if (size > 0) {
        // Allocate memory for name and copy data into it
        name = (char *)malloc(size + 1);
        if (name == NULL) {
            return 0; // Exit if memory allocation fails
        }
        memcpy(name, data, size);
        name[size] = '\0'; // Null terminate the string
    } else {
        return 0; // Exit if size is not sufficient
    }

    // Create a temporary file to obtain a valid group ID
    hid_t file_id = H5Fcreate("temp_file.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id >= 0) {
        // Create a group to obtain a valid group ID
        group_id = H5Gcreate2(file_id, "/temp_group", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        if (group_id >= 0) {
            // Call the function under test
            H5Gunlink(group_id, name);

            // Close the group
            H5Gclose(group_id);
        }
        // Close the file
        H5Fclose(file_id);
    }

    // Free allocated memory
    free(name);

    return 0;
}