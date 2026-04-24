#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Function-under-test
void hts_free(void *ptr);

int LLVMFuzzerTestOneInput_181(const uint8_t *data, size_t size) {
    // Allocate memory for fuzzing
    void *fuzz_ptr = malloc(size);
    if (fuzz_ptr == NULL) {
        return 0; // Return if memory allocation fails
    }

    // Copy the fuzzing data into the allocated memory
    memcpy(fuzz_ptr, data, size);

    // Call the function-under-test with the fuzzing data
    hts_free(fuzz_ptr);

    // No need to free fuzz_ptr as hts_free is expected to handle it

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

    LLVMFuzzerTestOneInput_181(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
