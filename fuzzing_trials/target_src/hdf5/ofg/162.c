#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_162(const uint8_t *data, size_t size) {
    // Ensure there is enough data to form a valid hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Use the first bytes of data to construct a hid_t
    hid_t file_id = *(const hid_t *)data;

    // Call the function-under-test
    herr_t result = H5Freset_page_buffering_stats(file_id);

    // Use the result in some way to avoid compiler optimizations
    if (result < 0) {
        // Handle error case if necessary
    }

    return 0;
}