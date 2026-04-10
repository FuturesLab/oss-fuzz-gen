#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <htslib/hts.h>
#include <htslib/hts_defs.h>
#include <htslib/bgzf.h>
#include <htslib/sam.h>
#include <htslib/tbx.h>

// Dummy read record function for demonstration purposes
int dummy_readrec(BGZF *fp, void *data, bam1_t *b, int *tid, int *beg, int *end) {
    return 0;
}

int LLVMFuzzerTestOneInput_197(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient for our needs
    if (size < sizeof(int) + 2 * sizeof(hts_pos_t)) {
        return 0;
    }

    // Create a dummy index
    hts_idx_t *idx = hts_idx_init(0, HTS_FMT_CSI, 0, 0, 0);

    // Extract parameters from the input data
    int tid = *((int *)data);
    hts_pos_t beg = *((hts_pos_t *)(data + sizeof(int)));
    hts_pos_t end = *((hts_pos_t *)(data + sizeof(int) + sizeof(hts_pos_t)));

    // Call the function-under-test
    hts_itr_t *itr = hts_itr_query(idx, tid, beg, end, dummy_readrec);

    // Clean up
    if (itr != NULL) {
        hts_itr_destroy(itr);
    }
    hts_idx_destroy(idx);

    return 0;
}