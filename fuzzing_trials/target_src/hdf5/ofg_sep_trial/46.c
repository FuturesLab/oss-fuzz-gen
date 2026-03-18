#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>
#include <string.h>

int LLVMFuzzerTestOneInput_46(const uint8_t *data, size_t size) {
    // Initialize variables needed for H5Aopen
    hid_t loc_id = H5I_INVALID_HID; // Invalid ID to start with
    hid_t aapl_id = H5P_DEFAULT;    // Default property list
    char attr_name[256];            // Buffer for attribute name

    // Ensure the data is large enough to extract necessary information
    if (size < 1) {
        return 0;
    }

    // Copy data into attr_name, ensuring null-termination
    size_t attr_name_len = size < 255 ? size : 255;
    memcpy(attr_name, data, attr_name_len);
    attr_name[attr_name_len] = '\0';

    // Attempt to open an attribute with the given parameters
    hid_t attr_id = H5Aopen(loc_id, attr_name, aapl_id);

    // Close the attribute if it was successfully opened
    if (attr_id >= 0) {
        H5Aclose(attr_id);
    }

    return 0;
}