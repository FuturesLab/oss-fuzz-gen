#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_81(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to extract an hid_t value
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract an hid_t value from the input data
    hid_t file_id = *((hid_t*)data);

    // Call the function-under-test
    H5Freset_mdc_hit_rate_stats(file_id);

    return 0;
}