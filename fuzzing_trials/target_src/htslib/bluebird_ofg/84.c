#include <stdint.h>
#include <stdlib.h>
#include "htslib/hts.h"
#include "/src/htslib/htslib/tbx.h"  // Include necessary library for hts_idx_t

int LLVMFuzzerTestOneInput_84(const uint8_t *data, size_t size) {
    // Initialize parameters for hts_idx_set_meta
    // Adjust the parameters to match the function signature of hts_idx_init
    uint64_t offset0 = 0; // Dummy offset
    int min_shift = 14; // Default minimum shift for CSI
    int n_lvls = 5; // Default number of levels for CSI
    hts_idx_t *idx = hts_idx_init(0, HTS_FMT_CSI, offset0, min_shift, n_lvls); // Create an index with dummy parameters
    
    // Ensure l_meta is not zero and does not exceed the size of data
    uint32_t l_meta = size > 4 ? *(uint32_t *)data % size : 1; 
    uint8_t *meta = (uint8_t *)malloc(l_meta); // Allocate memory for meta data
    if (meta == NULL) return 0; // Check for allocation failure
    int is_copy = 1; // Set is_copy to a non-zero value

    // Copy data to meta, ensuring no overflow
    if (size > 0) {
        size_t copy_size = l_meta < size ? l_meta : size;
        for (size_t i = 0; i < copy_size; i++) {
            meta[i] = data[i];
        }
    }

    // Call the function-under-test
    hts_idx_set_meta(idx, l_meta, meta, is_copy);

    // Clean up
    hts_idx_destroy(idx);
    free(meta);

    return 0;
}