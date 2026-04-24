#include <stdint.h>
#include <stddef.h>

// Declaration of the function-under-test
void hts_lib_shutdown();

// Placeholder for library initialization if applicable
// void hts_lib_init();

int LLVMFuzzerTestOneInput_157(const uint8_t *data, size_t size) {
    // Placeholder for initializing the library if applicable
    // hts_lib_init();

    // Since hts_lib_shutdown does not take any parameters,
    // we can directly call it to test its behavior.
    hts_lib_shutdown();

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

    LLVMFuzzerTestOneInput_157(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
