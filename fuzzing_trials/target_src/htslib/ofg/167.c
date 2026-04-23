#include <stdint.h>
#include <stddef.h>

// Function-under-test declaration
const char * hts_test_feature(unsigned int feature);

// Fuzzing harness
int LLVMFuzzerTestOneInput_167(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to extract an unsigned int
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Extract an unsigned int from the input data
    unsigned int feature = *((unsigned int *)data);

    // Call the function-under-test
    const char *result = hts_test_feature(feature);

    // Use the result in some way to avoid compiler optimizations
    if (result != NULL) {
        // Do something trivial with the result, like checking its length
        while (*result) {
            result++;
        }
    }

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

    LLVMFuzzerTestOneInput_167(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
