#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_126(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t file_id = -1;  // Invalid file ID
    unsigned int types = 0;  // Object types to count

    // Ensure the data size is sufficient to extract values
    if (size >= sizeof(hid_t) + sizeof(unsigned int)) {
        // Extract hid_t and unsigned int from the input data
        file_id = *((hid_t *)data);
        types = *((unsigned int *)(data + sizeof(hid_t)));
    }

    // Call the function-under-test
    ssize_t obj_count = H5Fget_obj_count(file_id, types);

    // Return 0 as required by LLVMFuzzerTestOneInput
    return 0;
}