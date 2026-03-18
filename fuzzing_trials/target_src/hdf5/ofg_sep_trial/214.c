#include <stdint.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_214(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract a valid hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract a hid_t from the input data
    hid_t file_id;
    memcpy(&file_id, data, sizeof(hid_t));

    // Call the function-under-test
    herr_t result = H5Fclear_elink_file_cache(file_id);

    // Use the result in some way to avoid compiler optimizations
    (void)result;

    return 0;
}