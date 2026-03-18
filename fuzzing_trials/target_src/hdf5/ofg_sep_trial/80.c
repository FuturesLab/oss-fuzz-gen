#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
    // Ensure that there is enough data to create a valid hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract a hid_t from the input data
    hid_t file_id = *(const hid_t *)data;

    // Call the function-under-test
    H5Freset_mdc_hit_rate_stats(file_id);

    return 0;
}