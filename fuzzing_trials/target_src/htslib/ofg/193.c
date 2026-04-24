#include <stdint.h>
#include <stddef.h>

// Function-under-test declaration
int64_t bam_auxB2i(const uint8_t *data, uint32_t size);

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_193(const uint8_t *data, size_t size) {
    // Ensure that size is non-zero and within a reasonable range for uint32_t
    if (size == 0 || size > UINT32_MAX) {
        return 0;
    }

    // Call the function-under-test
    int64_t result = bam_auxB2i(data, (uint32_t)size);

    // Use the result in some way to avoid compiler optimizations
    (void)result;

    return 0;
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

    LLVMFuzzerTestOneInput_193(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
