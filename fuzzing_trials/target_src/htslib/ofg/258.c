#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>
#include <htslib/hts.h>
#include <htslib/bgzf.h>

// Define constants for hts_idx_init
#define DUMMY_OFFSET0 0
#define DUMMY_MIN_SHIFT 14
#define DUMMY_N_LVLS 5

int LLVMFuzzerTestOneInput_258(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to contain a null-terminated string
    if (size < 1) {
        return 0;
    }

    // Create a temporary null-terminated string from the input data
    char *region = (char *)malloc(size + 1);
    if (!region) {
        return 0;
    }
    memcpy(region, data, size);
    region[size] = '\0';

    // Initialize dummy hts_idx_t and sam_hdr_t
    // Use hts_idx_init and sam_hdr_init for proper initialization
    hts_idx_t *dummy_idx = hts_idx_init(0, HTS_FMT_CSI, DUMMY_OFFSET0, DUMMY_MIN_SHIFT, DUMMY_N_LVLS);
    sam_hdr_t *dummy_hdr = sam_hdr_init();

    if (!dummy_idx || !dummy_hdr) {
        free(region);
        if (dummy_idx) hts_idx_destroy(dummy_idx);
        if (dummy_hdr) sam_hdr_destroy(dummy_hdr);
        return 0;
    }

    // Call the function-under-test
    hts_itr_t *itr = sam_itr_querys(dummy_idx, dummy_hdr, region);

    // Clean up
    if (itr) {
        hts_itr_destroy(itr);
    }
    free(region);
    hts_idx_destroy(dummy_idx);
    sam_hdr_destroy(dummy_hdr);

    return 0;
}