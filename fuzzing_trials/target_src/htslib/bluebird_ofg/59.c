#include <stdint.h>
#include <stddef.h>
#include "htslib/sam.h"
#include "htslib/hts.h"
#include "/src/htslib/htslib/bgzf.h"  // Required for BGZF functions
#include <stdlib.h>       // Required for malloc and free

int LLVMFuzzerTestOneInput_59(const uint8_t *data, size_t size) {
    // Check if size is non-zero to perform operations
    if (size == 0) {
        return 0;  // Not enough data to proceed
    }

    // Create a memory buffer from the input data
    BGZF *fp = bgzf_open("/dev/null", "w");  // Open a null BGZF file for writing
    if (!fp) {
        return 0;  // Failed to open BGZF file
    }

    // Write the data into the BGZF file
    if (bgzf_write(fp, data, size) < 0) {
        bgzf_close(fp);
        return 0;  // Failed to write data
    }

    // Create an index from the BGZF file
    hts_idx_t *idx = hts_idx_init(0, HTS_FMT_CSI, 0, 0, 0);
    if (!idx) {
        bgzf_close(fp);
        return 0;  // Failed to initialize index
    }

    // Finalize the index
    if (hts_idx_finish(idx, bgzf_tell(fp)) < 0) {
        hts_idx_destroy(idx);
        bgzf_close(fp);
        return 0;  // Failed to finalize index
    }

    // Declare and initialize variables for query
    int tid = 0;  // Example tid, can be varied for different tests
    hts_pos_t beg = 0;  // Start position
    hts_pos_t end = (hts_pos_t)size;  // End position based on size

    // Call the function-under-test
    hts_itr_t *itr = sam_itr_queryi(idx, tid, beg, end);

    // Cleanup
    if (itr != NULL) {
        hts_itr_destroy(itr);
    }
    hts_idx_destroy(idx);
    bgzf_close(fp);

    return 0;
}