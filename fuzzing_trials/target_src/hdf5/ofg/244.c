#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_244(const uint8_t *data, size_t size) {
    // Initialize variables
    hid_t attribute_id = H5I_INVALID_HID; // Invalid ID for testing
    char old_name[256];
    char new_name[256];

    // Ensure the data size is sufficient for two names
    if (size < 2) {
        return 0;
    }

    // Copy data into old_name and new_name
    size_t half_size = size / 2;
    size_t old_name_len = (half_size < 255) ? half_size : 255;
    size_t new_name_len = ((size - half_size) < 255) ? (size - half_size) : 255;

    memcpy(old_name, data, old_name_len);
    old_name[old_name_len] = '\0';

    memcpy(new_name, data + half_size, new_name_len);
    new_name[new_name_len] = '\0';

    // Call the function-under-test
    herr_t result = H5Arename(attribute_id, old_name, new_name);

    // Use the result in some way to avoid optimization out
    if (result < 0) {
        fprintf(stderr, "H5Arename failed\n");
    }

    return 0;
}