#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/hts.h>
#include <htslib/sam.h>
#include <htslib/cram.h>  // Include this for hts_idx_t and hts_itr_t definitions

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    // Ensure we have enough data to work with
    if (size < 1) {
        return 0;
    }

    // Create a memory stream from the input data
    htsFile *file = hts_open_format("data://", "r", NULL);
    if (!file) {
        return 0;
    }

    // Initialize index and iterator
    hts_idx_t *idx = hts_idx_load("data://", HTS_FMT_CRAI);
    if (!idx) {
        hts_close(file);
        return 0;
    }

    hts_itr_t *itr = hts_itr_query(idx, 0, 0, 0, 0);
    if (!itr) {
        hts_idx_destroy(idx);
        hts_close(file);
        return 0;
    }

    // Call the function-under-test
    int result = hts_itr_multi_cram(idx, itr);

    // Clean up
    hts_itr_destroy(itr);
    hts_idx_destroy(idx);
    hts_close(file);

    return result;
}

#ifdef __cplusplus
}
#endif
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

    LLVMFuzzerTestOneInput_25(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
