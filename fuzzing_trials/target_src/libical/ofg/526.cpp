#include <cstdint>
#include <cstdlib>
#include <cstring>

// Since the header file 'icalmemory.h' does not exist, we need to declare the function manually
extern "C" {
    // Declare the function under test
    void icalmemory_add_tmp_buffer(void *buffer);
}

extern "C" int LLVMFuzzerTestOneInput_526(const uint8_t *data, size_t size) {
    // Ensure that the size is non-zero to create a valid buffer
    if (size == 0) {
        return 0;
    }

    // Allocate a buffer to pass to the function
    void *buffer = malloc(size);
    if (buffer == nullptr) {
        return 0;
    }

    // Copy the data into the buffer
    memcpy(buffer, data, size);

    // Call the function under test
    icalmemory_add_tmp_buffer(buffer);

    // Free the buffer after the function call
    free(buffer);

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

    LLVMFuzzerTestOneInput_526(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
