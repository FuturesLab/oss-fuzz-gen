#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy
#include <hdf5.h>

int LLVMFuzzerTestOneInput_85(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    hid_t loc_id = H5I_INVALID_HID;  // Use an invalid ID for fuzzing
    char obj_name[256];
    char attr_name[256];
    hid_t lapl_id = H5P_DEFAULT;  // Default link access property list

    // Ensure the data size is sufficient for our needs
    if (size < 2) {
        return 0;
    }

    // Copy data into obj_name and attr_name, ensuring null-termination
    size_t obj_name_len = size / 2 < 255 ? size / 2 : 255;
    size_t attr_name_len = size - obj_name_len < 255 ? size - obj_name_len : 255;

    // Copy and null-terminate the strings
    memcpy(obj_name, data, obj_name_len);
    obj_name[obj_name_len] = '\0';

    memcpy(attr_name, data + obj_name_len, attr_name_len);
    attr_name[attr_name_len] = '\0';

    // Call the function-under-test
    H5Adelete_by_name(loc_id, obj_name, attr_name, lapl_id);

    return 0;
}