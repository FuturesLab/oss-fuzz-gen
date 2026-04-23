#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy
#include <htslib/hts.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_113(const uint8_t *data, size_t size) {
    // Initialize htsFile pointer
    htsFile *file = hts_open("test.bam", "r");
    if (!file) {
        return 0;
    }

    // Initialize hts_itr_t pointer
    hts_itr_t *itr = sam_itr_querys(file, "chr1:0-1000", NULL);
    if (!itr) {
        hts_close(file);
        return 0;
    }

    // Allocate a buffer for the data
    void *buffer = malloc(size);
    if (!buffer) {
        hts_itr_destroy(itr);
        hts_close(file);
        return 0;
    }

    // Copy the input data to the buffer
    memcpy(buffer, data, size);

    // Call the function-under-test
    int result = hts_itr_multi_next(file, itr, buffer);

    // Clean up
    free(buffer);
    hts_itr_destroy(itr);
    hts_close(file);

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

    LLVMFuzzerTestOneInput_113(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
