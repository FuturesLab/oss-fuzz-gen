#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/hts.h"
#include "/src/htslib/htslib/hts_defs.h"
#include "htslib/sam.h"
#include <htslib/tbx.h>
#include "/src/htslib/htslib/bgzf.h" // Include for BGZF
#include "/src/htslib/htslib/tbx.h" // Correct path for hts_idx_t related functions

// Dummy readrec function with correct signature
int dummy_readrec(BGZF *fp, void *vp, void *b, int *tid, hts_pos_t *beg, hts_pos_t *end) {
    return 0; // Dummy implementation
}

int LLVMFuzzerTestOneInput_143(const uint8_t *data, size_t size) {
    // Ensure size is large enough to contain tid, beg, and end
    if (size < sizeof(int) + 2 * sizeof(hts_pos_t)) {
        return 0; // Not enough data to construct the parameters
    }

    // Safely extract parameters
    int tid = *((int *)data);
    hts_pos_t beg = *((hts_pos_t *)(data + sizeof(int)));
    hts_pos_t end = *((hts_pos_t *)(data + sizeof(int) + sizeof(hts_pos_t)));

    // Ensure beg <= end to avoid invalid range
    if (beg > end) {
        return 0;
    }

    // Use a valid hts_idx_t object
    hts_idx_t *idx = hts_idx_load("dummy.bam", HTS_FMT_BAI); // Load a dummy index for testing
    if (idx == NULL) {
        return 0; // Failed to load index
    }

    // Call the function-under-test
    hts_itr_t *itr = hts_itr_query(idx, tid, beg, end, dummy_readrec);

    // Clean up
    if (itr != NULL) {
        hts_itr_destroy(itr);
    }
    hts_idx_destroy(idx);

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_143(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
