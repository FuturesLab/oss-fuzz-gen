#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_240(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t attribute_id = H5I_INVALID_HID; // Invalid ID to start with
    char old_name[256];
    char new_name[256];

    // Ensure that size is sufficient to extract two names
    if (size < 2) {
        return 0;
    }

    // Copy data into old_name and new_name, ensuring null-termination
    size_t old_name_len = size / 2 < 255 ? size / 2 : 255;
    size_t new_name_len = size - old_name_len < 255 ? size - old_name_len : 255;

    memcpy(old_name, data, old_name_len);
    old_name[old_name_len] = '\0';

    memcpy(new_name, data + old_name_len, new_name_len);
    new_name[new_name_len] = '\0';

    // Call the function-under-test
    herr_t result = H5Arename(attribute_id, old_name, new_name);

    // Return success
    return 0;
}