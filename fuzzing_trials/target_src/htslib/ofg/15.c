#include <stdint.h>
#include <stdlib.h>
#include <htslib/hts.h>
#include <htslib/bgzf.h> // Include this header for BGZF related functions
#include <htslib/tbx.h>  // Include this header for tabix related functions

int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    // Initialize a BGZF file pointer for index creation
    BGZF *bgzf = bgzf_open("/dev/null", "w");
    if (bgzf == NULL) {
        return 0;
    }

    // Initialize the index
    hts_idx_t *idx = hts_idx_init(0, HTS_FMT_CSI, bgzf, 0, 0);
    if (idx == NULL) {
        bgzf_close(bgzf);
        return 0;
    }

    uint64_t val = 0;
    if (size >= sizeof(uint64_t)) {
        val = *((uint64_t *)data);
    }

    // Call the function-under-test
    hts_idx_finish(idx, val);

    // Clean up
    hts_idx_destroy(idx);
    bgzf_close(bgzf);
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

    LLVMFuzzerTestOneInput_15(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
