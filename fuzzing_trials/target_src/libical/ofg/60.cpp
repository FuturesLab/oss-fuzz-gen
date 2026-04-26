#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring> // Include this header for memcpy

extern "C" {
    void icalmemory_free_buffer(void *);
}

extern "C" int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    // Ensure the size is non-zero to allocate memory
    if (size == 0) {
        return 0;
    }

    // Allocate memory and copy the input data into it
    void *buffer = malloc(size);
    if (buffer == nullptr) {
        return 0;
    }

    // Copy the data to the allocated buffer
    memcpy(buffer, data, size);

    // Call the function-under-test
    icalmemory_free_buffer(buffer);

    // No need to free buffer here as icalmemory_free_buffer is expected to handle it

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

    LLVMFuzzerTestOneInput_60(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
