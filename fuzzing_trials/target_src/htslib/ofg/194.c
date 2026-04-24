#include <stdint.h>
#include <stddef.h>
#include <limits.h> // Include this to ensure UINT32_MAX is defined

// Function-under-test declaration
int64_t bam_auxB2i(const uint8_t *data, uint32_t size);

int LLVMFuzzerTestOneInput_194(const uint8_t *data, size_t size) {
    // Ensure that the size is not zero to avoid passing a NULL pointer
    if (size == 0) {
        return 0;
    }

    // Cast size to uint32_t, ensuring it doesn't exceed the maximum value of uint32_t
    uint32_t converted_size = (uint32_t)(size > UINT32_MAX ? UINT32_MAX : size);

    // Call the function-under-test
    int64_t result = bam_auxB2i(data, converted_size);

    // Use the result to prevent compiler optimizations from removing the call
    (void)result;

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

    LLVMFuzzerTestOneInput_194(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
