#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring> // Include the header for memcpy

extern "C" {
    void icalmemory_free_buffer(void *);
}

extern "C" int LLVMFuzzerTestOneInput_59(const uint8_t *data, size_t size) {
    // Allocate memory for the buffer with the size of the input data
    void *buffer = malloc(size);
    if (buffer == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Copy the input data into the allocated buffer
    memcpy(buffer, data, size);

    // Call the function-under-test
    icalmemory_free_buffer(buffer);

    // No need to free the buffer, as icalmemory_free_buffer is expected to handle it

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

    LLVMFuzzerTestOneInput_59(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
