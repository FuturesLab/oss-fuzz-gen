#include <stdlib.h>
#include <string.h>
#include <stdint.h> // Include for uint8_t

extern "C" {
    // Assuming icalmemory_resize_buffer is declared in a different way since icalmemory.h does not exist
    // Declare the function prototype for icalmemory_resize_buffer here
    void* icalmemory_resize_buffer(void* buffer, size_t size);
}

extern "C" int LLVMFuzzerTestOneInput_960(const uint8_t *data, size_t size) {
    // Initialize a buffer with some data
    size_t initial_size = 10;
    void *buffer = malloc(initial_size);
    if (buffer == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Fill the buffer with some initial data
    memset(buffer, 'A', initial_size);

    // Use the size from the fuzzer input to resize the buffer
    size_t new_size = size > 0 ? size : 1; // Ensure new_size is non-zero
    void *resized_buffer = icalmemory_resize_buffer(buffer, new_size);

    // Check if the resized buffer is not NULL
    if (resized_buffer == NULL) {
        free(buffer);
        return 0;
    }

    // Free the resized buffer
    free(resized_buffer);

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

    LLVMFuzzerTestOneInput_960(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
