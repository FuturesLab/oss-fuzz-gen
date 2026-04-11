#include <stdint.h>
#include <stdlib.h>
#include <htslib/sam.h>
#include <htslib/hts.h>
#include <htslib/hts_defs.h> // Include for hts_idx_t

int LLVMFuzzerTestOneInput_46(const uint8_t *data, size_t size) {
    // Allocate memory for hts_idx_t using a pointer, as its size is not known
    hts_idx_t *idx = NULL; // We cannot directly allocate hts_idx_t due to its incomplete type
    sam_hdr_t *hdr = sam_hdr_init();
    hts_reglist_t reglist;
    unsigned int flags = 0;

    // Initialize reglist with some dummy values
    reglist.reg = (char *)"chr1";
    reglist.min_beg = 0;
    reglist.max_end = 1000;
    reglist.count = 1;
    reglist.intervals = (hts_pair_pos_t *)malloc(sizeof(hts_pair_pos_t));
    reglist.intervals[0].beg = 0;
    reglist.intervals[0].end = 1000;

    // Call the function-under-test
    hts_itr_t *itr = sam_itr_regions(idx, hdr, &reglist, flags);

    // Cleanup
    if (itr != NULL) {
        hts_itr_destroy(itr);
    }
    sam_hdr_destroy(hdr);
    free(reglist.intervals);
    // No need to free idx as it was not allocated

    return 0;
}