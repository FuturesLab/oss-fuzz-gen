#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>
#include <string.h>

int LLVMFuzzerTestOneInput_208(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t loc_id = H5I_INVALID_HID;  // Initialize to an invalid ID
    char attr_name[256] = {0};       // Buffer for attribute name

    // Ensure the data size is sufficient for a meaningful attribute name
    if (size < 1) {
        return 0;
    }

    // Copy data to attr_name, ensuring null-termination
    size_t copy_size = size < sizeof(attr_name) - 1 ? size : sizeof(attr_name) - 1;
    memcpy(attr_name, data, copy_size);
    attr_name[copy_size] = '\0';

    // Call the function-under-test
    hid_t attr_id = H5Aopen_name(loc_id, attr_name);

    // Normally, we would do something with attr_id, like checking if it's valid
    // Close the attribute if it was successfully opened
    if (attr_id >= 0) {
        H5Aclose(attr_id);
    }

    return 0;
}