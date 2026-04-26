#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    // Declare the function prototype for icalmemory_resize_buffer
    void *icalmemory_resize_buffer(void *buffer, size_t new_size);
}

extern "C" int LLVMFuzzerTestOneInput_959(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0; // No operation if input size is zero
    }

    // Initialize a buffer with some initial data
    size_t initial_size = size; // Use the size provided by the fuzzer
    void *buffer = malloc(initial_size);
    if (buffer == NULL) {
        return 0; // Early exit if memory allocation fails
    }

    // Copy the fuzzer-provided data into the buffer
    memcpy(buffer, data, initial_size);

    // Call the function-under-test with the buffer and a new size
    size_t new_size = size * 2; // Resize to a different size to ensure function execution
    void *resized_buffer = icalmemory_resize_buffer(buffer, new_size);

    // Free the resized buffer if it's different from the original
    if (resized_buffer != buffer) {
        free(resized_buffer);
    } else {
        free(buffer);
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

    LLVMFuzzerTestOneInput_959(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
