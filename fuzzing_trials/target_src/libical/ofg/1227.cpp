#include <cstddef>
#include <cstdint>
#include <cstdlib> // Include for malloc and free

extern "C" {
    #include <libical/ical.h> // Include the correct header for libical
}

extern "C" int LLVMFuzzerTestOneInput_1227(const uint8_t *data, size_t size) {
    // Ensure size is non-zero to avoid unnecessary calls with zero size
    if (size == 0) {
        return 0;
    }

    // Call the function-under-test with the provided size
    void *buffer = icalmemory_new_buffer(size);

    // Normally, you would perform additional operations on the buffer here,
    // but since the task is only to call the function, we will skip that.

    // It's good practice to free allocated memory if applicable
    if (buffer != nullptr) {
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

    LLVMFuzzerTestOneInput_1227(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
