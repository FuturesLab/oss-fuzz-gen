#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_163(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract a valid hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract a hid_t from the input data
    hid_t file_id = *((hid_t*)data);

    // Call the function-under-test
    H5Freset_page_buffering_stats(file_id);

    return 0;
}