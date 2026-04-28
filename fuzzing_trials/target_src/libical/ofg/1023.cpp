#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include <libical/icalmemory.h>
}

extern "C" int LLVMFuzzerTestOneInput_1023(const uint8_t *data, size_t size) {
    // Ensure size is non-zero to avoid calling with zero-size
    if (size == 0) {
        return 0;
    }

    // Call the function-under-test with the given size
    void *buffer = icalmemory_tmp_buffer(size);

    // Normally, you would do something with the buffer, but since this is a
    // fuzzing harness, we are primarily interested in calling the function
    // to check for memory corruption or crashes.

    // No need to free the buffer as icalmemory_tmp_buffer is assumed to manage its own memory

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

    LLVMFuzzerTestOneInput_1023(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
