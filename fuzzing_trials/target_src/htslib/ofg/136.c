#include <stdint.h>
#include <stdlib.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_136(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract a uint64_t value
    if (size < sizeof(uint64_t)) {
        return 0;
    }

    // Initialize a hts_idx_t structure
    hts_idx_t *index = hts_idx_init(0, HTS_FMT_CSI, 0, 0, 0);
    if (index == NULL) {
        return 0;
    }

    // Extract a uint64_t value from the data
    uint64_t value = *((uint64_t *)data);

    // Call the function-under-test
    int result = hts_idx_finish(index, value);

    // Clean up
    hts_idx_destroy(index);

    return 0;
}