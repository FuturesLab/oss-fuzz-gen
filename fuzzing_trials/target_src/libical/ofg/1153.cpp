#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/icaltimezone.h> // Include the correct header for icaltimezone functions

    // Declare the function to be used
    icaltimezone *icaltimezone_new();
    void icaltimezone_free(icaltimezone *zone, int free_struct);
}

extern "C" int LLVMFuzzerTestOneInput_1153(const uint8_t *data, size_t size) {
    // Declare and initialize necessary variables
    icaltimezone *zone = icaltimezone_new();
    int free_struct = 1;  // Non-zero value to indicate freeing the structure

    // Call the function-under-test
    icaltimezone_free(zone, free_struct);

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

    LLVMFuzzerTestOneInput_1153(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
