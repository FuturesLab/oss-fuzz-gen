#include <stdint.h>
#include <stdlib.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_135(const uint8_t *data, size_t size) {
    // Initialize variables
    hts_idx_t *idx = hts_idx_init(0, HTS_FMT_CSI, 0, 0, 0);  // Create a new index with default parameters
    uint64_t final_offset = 0;

    // Ensure idx is not NULL
    if (idx == NULL) {
        return 0;
    }

    // If size is sufficient, use data to set the final_offset
    if (size >= sizeof(uint64_t)) {
        final_offset = *((uint64_t *)data);
    }

    // Call the function-under-test
    int result = hts_idx_finish(idx, final_offset);

    // Clean up
    hts_idx_destroy(idx);

    return 0;
}