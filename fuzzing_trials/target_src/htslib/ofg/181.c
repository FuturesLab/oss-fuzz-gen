#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_181(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    // Initialize an index with appropriate parameters
    int n = 0; // Number of reference sequences, set to 0 for simplicity
    int fmt = HTS_FMT_CSI; // Format type
    uint64_t offset0 = 0; // Initial offset
    int min_shift = 14; // Minimum shift, a common default value
    int n_lvls = 5; // Number of levels, a common default value
    hts_idx_t *idx = hts_idx_init(n, fmt, offset0, min_shift, n_lvls);

    uint32_t meta_type = 0; // Example metadata type
    uint8_t *meta_data = NULL;
    int meta_data_len = 0;

    // Ensure size is sufficient for metadata
    if (size > sizeof(uint32_t)) {
        meta_data_len = size - sizeof(uint32_t);
        meta_data = (uint8_t *)malloc(meta_data_len);
        if (meta_data == NULL) {
            hts_idx_destroy(idx);
            return 0;
        }
        // Copy data to meta_data
        for (int i = 0; i < meta_data_len; ++i) {
            meta_data[i] = data[i];
        }
    }

    // Call the function-under-test
    hts_idx_set_meta(idx, meta_type, meta_data, meta_data_len);

    // Clean up
    free(meta_data);
    hts_idx_destroy(idx);

    return 0;
}