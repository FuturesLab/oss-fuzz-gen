#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Function signature for the function-under-test
const char *hts_parse_reg(const char *region, int *beg, int *end);

int LLVMFuzzerTestOneInput_79(const uint8_t *data, size_t size) {
    // Ensure that the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the region string and ensure it is null-terminated
    char *region = (char *)malloc(size + 1);
    if (region == NULL) {
        return 0;
    }
    memcpy(region, data, size);
    region[size] = '\0';

    // Initialize beg and end to non-NULL values
    int beg = 0;
    int end = 0;

    // Call the function-under-test
    const char *result = hts_parse_reg(region, &beg, &end);

    // Free the allocated memory for the region
    free(region);

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

    LLVMFuzzerTestOneInput_79(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
