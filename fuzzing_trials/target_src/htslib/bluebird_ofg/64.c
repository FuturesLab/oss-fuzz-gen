#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h"
#include "htslib/hts.h"
#include "/src/htslib/htslib/hts_defs.h" // Include for HTS_FMT_CSI

int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for meaningful fuzzing
    if (size < 3) {
        return 0;
    }

    // Create a mock hts_idx_t object
    // Provide appropriate values for offset0, min_shift, and n_lvls
    hts_idx_t *idx = hts_idx_init(0, HTS_FMT_CSI, 0, 14, 5);

    // Create a mock sam_hdr_t object
    sam_hdr_t *hdr = sam_hdr_init();

    // Prepare a query string from the input data
    // Ensure null termination

    // Begin mutation: Producer.SPLICE_MUTATOR - Spliced data flow from sam_hdr_init to sam_itr_regarray using the plateau pool
    char **regions = NULL;
    unsigned int n = 1;
    // Ensure dataflow is valid (i.e., non-null)
    if (!idx) {
    	return 0;
    }
    // Ensure dataflow is valid (i.e., non-null)
    if (!hdr) {
    	return 0;
    }
    hts_itr_t* ret_sam_itr_regarray_mfxnj = sam_itr_regarray(idx, hdr, regions, n);
    if (ret_sam_itr_regarray_mfxnj == NULL){
    	return 0;
    }
    // End mutation: Producer.SPLICE_MUTATOR
    
    char *query = (char *)malloc(size + 1);
    memcpy(query, data, size);
    query[size] = '\0';

    // Call the function-under-test
    hts_itr_t *itr = sam_itr_querys(idx, hdr, query);

    // Clean up
    if (itr != NULL) {
        hts_itr_destroy(itr);
    }

    // Begin mutation: Producer.SPLICE_MUTATOR - Spliced data flow from sam_itr_querys to sam_itr_regions using the plateau pool
    hts_reglist_t *reglist = (hts_reglist_t *)malloc(sizeof(hts_reglist_t));
    unsigned int flags = 0;
    // Ensure dataflow is valid (i.e., non-null)
    if (!idx) {
    	return 0;
    }
    // Ensure dataflow is valid (i.e., non-null)
    if (!hdr) {
    	return 0;
    }
    hts_itr_t* ret_sam_itr_regions_zbfnj = sam_itr_regions(idx, hdr, reglist, flags);
    if (ret_sam_itr_regions_zbfnj == NULL){
    	return 0;
    }
    // End mutation: Producer.SPLICE_MUTATOR
    
    hts_idx_destroy(idx);
    sam_hdr_destroy(hdr);
    free(query);

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

    LLVMFuzzerTestOneInput_64(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
