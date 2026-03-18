#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t loc_id = H5I_INVALID_HID;  // Initialize with an invalid ID
    const char *name = "test_object";
    size_t bufsize = 1024;
    char *comment = (char *)malloc(bufsize);

    // Ensure that the comment buffer is not NULL
    if (comment == NULL) {
        return 0;
    }

    // Attempt to open a file and create a group to get a valid hid_t
    hid_t file_id = H5Fcreate("testfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id >= 0) {
        hid_t group_id = H5Gcreate2(file_id, name, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        if (group_id >= 0) {
            loc_id = group_id;  // Use the valid group ID
        }
    }

    // Use the input data to modify the comment buffer
    if (size > 0 && size < bufsize) {
        memcpy(comment, data, size);
        comment[size] = '\0';  // Ensure null-termination
    }

    // Call the function-under-test
    int result = H5Gget_comment(loc_id, name, bufsize, comment);

    // Clean up resources
    if (loc_id >= 0) {
        H5Gclose(loc_id);
    }
    if (file_id >= 0) {
        H5Fclose(file_id);
    }
    free(comment);

    return 0;
}