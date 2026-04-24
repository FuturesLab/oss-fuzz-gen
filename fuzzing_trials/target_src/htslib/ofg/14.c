#include <stdint.h>
#include <stdlib.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hts_idx_t *idx = hts_idx_init(0, HTS_FMT_CSI, 0, 0, 0);
    uint64_t final_offset = 0;

    // Ensure size is sufficient to extract a uint64_t value
    if (size >= sizeof(uint64_t)) {
        // Use the first 8 bytes of data to set final_offset
        final_offset = *(const uint64_t *)data;
    }

    // Call the function-under-test
    hts_idx_finish(idx, final_offset);

    // Clean up
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

    LLVMFuzzerTestOneInput_14(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
