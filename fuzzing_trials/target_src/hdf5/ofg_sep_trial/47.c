#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t loc_id = H5I_INVALID_HID; // Use an invalid ID as a placeholder
    char attr_name[256];
    hid_t aapl_id = H5P_DEFAULT; // Default attribute access property list

    // Ensure size is sufficient to extract a valid attribute name
    if (size < 1) {
        return 0; // Not enough data to proceed
    }

    // Copy data into attr_name ensuring null-termination
    size_t attr_name_len = size < sizeof(attr_name) ? size : sizeof(attr_name) - 1;
    memcpy(attr_name, data, attr_name_len);
    attr_name[attr_name_len] = '\0';

    // Call the function-under-test
    hid_t attr_id = H5Aopen(loc_id, attr_name, aapl_id);

    // Close the attribute if it was successfully opened
    if (attr_id >= 0) {
        H5Aclose(attr_id);
    }

    return 0;
}