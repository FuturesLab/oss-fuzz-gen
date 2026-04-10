#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <htslib/hts.h>
#include <htslib/hts_defs.h>
#include <htslib/tbx.h> // Include this header to access the complete definition of hts_idx_t

int LLVMFuzzerTestOneInput_65(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    tbx_t *tbx = tbx_index_load("example.vcf.gz"); // Load an example index file
    if (tbx == NULL) {
        return 0;
    }
    hts_idx_t *idx = tbx->idx; // Get the index from the tbx structure
    uint32_t meta_size = 0;
    uint8_t *meta;

    // Ensure idx is not NULL
    if (idx == NULL) {
        tbx_destroy(tbx); // Clean up tbx if idx is NULL
        return 0;
    }

    // Call the function-under-test
    meta = hts_idx_get_meta(idx, &meta_size);

    // Perform any necessary cleanup
    tbx_destroy(tbx);

    return 0;
}