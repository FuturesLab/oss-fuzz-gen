#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include "htslib/hts.h"
#include "/src/htslib/htslib/hts_defs.h"
#include "htslib/sam.h"  // Include this to define bam1_t
#include "/src/htslib/htslib/bgzf.h" // Include this for BGZF

// Dummy implementations of the function pointers required by hts_itr_querys
static int dummy_name2id(void *hdr, const char *name) {
    return 0; // Dummy implementation
}

static int dummy_itr_query_func(const void *hdr, const char *name, hts_itr_t *iter) {
    return 0; // Dummy implementation
}

static int dummy_readrec_func(BGZF *fp, void *hdr, void *data, bam1_t *b, int *tid, int *beg, int *end) {
    return 0; // Dummy implementation
}

int LLVMFuzzerTestOneInput_99(const uint8_t *data, size_t size) {
    // Initialize necessary variables
    hts_idx_t *idx = (hts_idx_t *)data;  // Cast data to hts_idx_t pointer
    const char *region = "chr1:1000-2000";  // Example region string
    void *hdr = NULL;  // Placeholder for header, can be NULL for fuzzing

    // Call the function-under-test
    hts_itr_t *itr = hts_itr_querys(idx, region, dummy_name2id, hdr, dummy_itr_query_func, dummy_readrec_func);

    // Clean up
    if (itr != NULL) {
        hts_itr_destroy(itr);
    }

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

    LLVMFuzzerTestOneInput_99(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
