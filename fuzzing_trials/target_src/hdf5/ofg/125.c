#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_125(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract parameters
    if (size < sizeof(hid_t) + sizeof(unsigned int)) {
        return 0;
    }

    // Extract parameters from data
    hid_t file_id = *(const hid_t *)data;
    unsigned int types = *(const unsigned int *)(data + sizeof(hid_t));

    // Call the function-under-test
    ssize_t obj_count = H5Fget_obj_count(file_id, types);

    // Use obj_count in some way to avoid compiler optimizations removing the call
    if (obj_count < 0) {
        // Handle error case if needed
    }

    return 0;
}