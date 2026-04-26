#include <cstddef>
#include <cstdint>
#include <cstdlib> // Include for malloc and free
#include <cstring> // Include for memset

extern "C" {
    // The icalmemory.h file does not exist, so we will declare the function prototype directly
    void* icalmemory_tmp_buffer(size_t size);
}

extern "C" int LLVMFuzzerTestOneInput_1024(const uint8_t *data, size_t size) {
    // Ensure that size is not zero to avoid calling the function with a size of zero
    if (size == 0) {
        return 0;
    }

    // Call the function-under-test with the given size
    void *result = icalmemory_tmp_buffer(size);

    // Optionally, you can perform some operations with `result` to ensure it is not NULL
    if (result != nullptr) {
        // Simulate using the result to avoid compiler optimizations removing it
        memset(result, 0, size);
    }

    // Free the allocated memory if needed
    free(result);

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

    LLVMFuzzerTestOneInput_1024(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
