#include <stdint.h>
#include <stdlib.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_102(const uint8_t *data, size_t size) {
    if (size < sizeof(int)) {
        return 0;
    }

    // Create a sam_hdr_t object
    sam_hdr_t *hdr = (sam_hdr_t *)malloc(sizeof(sam_hdr_t));
    if (!hdr) {
        return 0;
    }

    // Initialize the sam_hdr_t object with some non-NULL values
    hdr->n_targets = 1;
    hdr->target_len = (uint32_t *)malloc(sizeof(uint32_t) * hdr->n_targets);
    if (!hdr->target_len) {
        free(hdr);
        return 0;
    }
    hdr->target_len[0] = 1000; // Example target length

    // Extract an integer from the input data
    int tid = *(int *)data;

    // Ensure tid is within the valid range
    if (tid < 0 || tid >= hdr->n_targets) {
        free(hdr->target_len);
        free(hdr);
        return 0;
    }

    // Call the function-under-test
    hts_pos_t len = sam_hdr_tid2len(hdr, tid);

    // Clean up
    free(hdr->target_len);
    free(hdr);

    return 0;
}