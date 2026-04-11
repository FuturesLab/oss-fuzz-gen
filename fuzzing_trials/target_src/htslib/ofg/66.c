#include <stdint.h>
#include <stdlib.h>
#include <htslib/hts.h>
#include <htslib/tbx.h>  // Include the header that provides functions to work with hts_idx_t

int LLVMFuzzerTestOneInput_66(const uint8_t *data, size_t size) {
    // Use an API function to create an index instead of direct allocation
    hts_idx_t *idx = tbx_index_load2("dummy", "dummy.tbi");

    // Ensure that the idx is not NULL
    if (idx == NULL) {
        return 0;
    }

    uint32_t meta_size = 0;

    // Call the function-under-test
    uint8_t *meta = hts_idx_get_meta(idx, &meta_size);

    // Free allocated memory if necessary
    if (meta != NULL) {
        free(meta);
    }
    
    // Use the appropriate function to free the index
    hts_idx_destroy(idx);

    return 0;
}