#include <stdint.h>
#include <stddef.h>

// Assuming the header file for hts_lib_shutdown_158 is included
// Include the necessary header file for hts_lib_shutdown_158
// #include "hts_lib.h" // Uncomment and replace with the actual header file if available

// Mock implementation of hts_lib_shutdown_158 for demonstration purposes
void hts_lib_shutdown_158() {
    // Actual implementation would be in the library
}

int LLVMFuzzerTestOneInput_158(const uint8_t *data, size_t size) {
    // Call the function-under-test
    hts_lib_shutdown_158();

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

    LLVMFuzzerTestOneInput_158(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
