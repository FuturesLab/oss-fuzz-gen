#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/hts.h>
#include <htslib/tbx.h>
#include <htslib/bgzf.h>  // Include this for BGZF-related functions

int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size) {
    hts_idx_t *idx = NULL;
    BGZF *bgzf = NULL;

    // Create a temporary BGZF file in memory
    bgzf = bgzf_open("mem:", "w");
    if (bgzf == NULL) {
        return 0;
    }

    // Write the input data to the BGZF file
    if (bgzf_write(bgzf, data, size) < 0) {
        bgzf_close(bgzf);
        return 0;
    }

    // Close the BGZF file to flush and finalize it
    if (bgzf_close(bgzf) < 0) {
        return 0;
    }

    // Try to load an index from the BGZF file
    idx = hts_idx_load("mem:", HTS_FMT_BAI);
    if (idx == NULL) {
        return 0;
    }

    // Call the function-under-test
    int result = hts_idx_fmt(idx);

    // Free allocated index
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_35(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
