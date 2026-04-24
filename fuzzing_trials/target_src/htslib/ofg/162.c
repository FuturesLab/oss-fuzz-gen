#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h> // Include this for memcpy
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_162(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient to extract an int
    if (size < sizeof(int)) {
        return 0;
    }

    // Create a temporary htsFile structure
    htsFile *file = hts_open("temp.bam", "wb");
    if (file == NULL) {
        return 0;
    }

    // Extract an int value from the data
    int cache_size;
    memcpy(&cache_size, data, sizeof(int));

    // Call the function-under-test
    hts_set_cache_size(file, cache_size);

    // Close the htsFile
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

    LLVMFuzzerTestOneInput_162(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
