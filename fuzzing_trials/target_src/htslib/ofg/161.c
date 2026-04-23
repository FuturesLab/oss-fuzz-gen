#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_161(const uint8_t *data, size_t size) {
    htsFile *file = NULL;
    int cache_size;

    // Ensure we have enough data to extract an integer for cache size
    if (size < sizeof(int)) {
        return 0;
    }

    // Initialize cache_size from the input data
    cache_size = *((int *)data);

    // Open a temporary file as an htsFile
    file = hts_open("/tmp/fuzzfile.bam", "wb");
    if (file == NULL) {
        return 0;
    }

    // Call the function-under-test with the parameters
    hts_set_cache_size(file, cache_size);

    // Close the file
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

    LLVMFuzzerTestOneInput_161(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
