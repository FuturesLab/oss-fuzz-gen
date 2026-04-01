#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    // Initialize variables
    hid_t loc_id = H5I_INVALID_HID;
    char *name = NULL;

    // Ensure there's enough data to create a valid string
    if (size > 0) {
        // Allocate memory for the name and copy data into it
        name = (char *)malloc(size + 1);
        if (name == NULL) {
            return 0;
        }
        memcpy(name, data, size);
        name[size] = '\0'; // Null-terminate the string

        // Create a HDF5 file in memory to obtain a valid hid_t
        hid_t file_id = H5Fcreate("testfile", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
        if (file_id >= 0) {
            loc_id = file_id;
        }
    }

    // Call the function-under-test
    H5Funmount(loc_id, name);

    // Clean up
    if (loc_id != H5I_INVALID_HID) {
        H5Fclose(loc_id);
    }
    free(name);

    return 0;
}