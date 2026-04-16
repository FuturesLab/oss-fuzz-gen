#include <stdint.h>
#include <stddef.h>
#include "htslib/hts.h"
#include "/src/htslib/htslib/hts_defs.h"
#include "/src/htslib/hts_internal.h" // Correct path for hts_idx_t and related functions

int LLVMFuzzerTestOneInput_90(const uint8_t *data, size_t size) {
    // Ensure there is enough data to proceed
    if (size < sizeof(uint64_t) + 1) {
        return 0;
    }

    // Initialize parameters for hts_idx_init
    int n = 1;  // Number of reference sequences, must be > 0
    int min_shift = 14;  // Minimum shift, typically 14 for BAM
    uint64_t n_lvls = 5;  // Number of levels, typically 5 for BAM
    int fmt = HTS_FMT_CSI;  // Format, HTS_FMT_CSI is a common choice
    int flags = 0;  // Flags, 0 for default behavior

    // Call the function-under-test
    hts_idx_t *idx = hts_idx_init(n, min_shift, n_lvls, fmt, flags);

    // Use the input data to simulate some operations on the index
    if (idx != NULL) {
        // Use the input data to create a fake bin and offset
        uint64_t bin = data[0] % 37450; // A typical bin range for BAM
        uint64_t offset = *((uint64_t *)(data + 1));

        // Add an entry to the index
        int is_mapped = 1;  // Assuming the entry is mapped
        hts_idx_push(idx, 0, bin, offset, offset + 1, is_mapped);
        
        // Finalize the index to simulate a complete operation
        hts_idx_finish(idx, UINT64_MAX);

        // Clean up
        hts_idx_destroy(idx);
    }

    return 0;
}