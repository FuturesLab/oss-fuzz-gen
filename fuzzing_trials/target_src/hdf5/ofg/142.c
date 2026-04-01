#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_142(const uint8_t *data, size_t size) {
    // Check if the data size is sufficient to extract a valid hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract a hid_t from the input data
    hid_t file_id = *((hid_t*)data);

    // Call the function-under-test
    hssize_t free_space = H5Fget_freespace(file_id);

    // Use the result to prevent compiler optimizations
    volatile hssize_t result = free_space;

    return 0;
}