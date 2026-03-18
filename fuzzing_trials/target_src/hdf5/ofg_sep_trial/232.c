#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_232(const uint8_t *data, size_t size) {
    // Initialize variables
    hid_t object_id = 1; // Assuming a valid object ID for testing
    char attr_name[256]; // Buffer for attribute name

    // Ensure size is not zero and does not exceed buffer size
    if (size == 0 || size >= sizeof(attr_name)) {
        return 0;
    }

    // Copy data to attr_name and null-terminate it
    memcpy(attr_name, data, size);
    attr_name[size] = '\0';

    // Call the function-under-test
    htri_t result = H5Aexists(object_id, attr_name);

    // Use the result to avoid unused variable warning
    if (result < 0) {
        // Handle error if needed
    }

    return 0;
}