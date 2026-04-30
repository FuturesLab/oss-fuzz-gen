#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    // Since "icalmemory.h" does not exist, we must assume the function
    // `icalmemory_add_tmp_buffer` is declared elsewhere in the project.
    // We declare it here to avoid compilation errors.
    void icalmemory_add_tmp_buffer(void *buffer);
}

extern "C" int LLVMFuzzerTestOneInput_527(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a non-null buffer
    if (size == 0) {
        return 0;
    }

    // Allocate a buffer and copy the data into it
    void *buffer = malloc(size);
    if (buffer == nullptr) {
        return 0;
    }
    memcpy(buffer, data, size);

    // Call the function-under-test
    icalmemory_add_tmp_buffer(buffer);

    // Free the allocated buffer
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

    LLVMFuzzerTestOneInput_527(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
