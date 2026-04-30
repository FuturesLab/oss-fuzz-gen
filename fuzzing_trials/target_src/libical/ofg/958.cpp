#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// Assuming the function is part of a C library, we need to wrap it with extern "C"
extern "C" {
    // Include the necessary header for the function-under-test
    #include "libical/icalcomponent.h"
}

// Fuzzing harness for the function icalcomponent_isa_component
extern "C" int LLVMFuzzerTestOneInput_958(const uint8_t *data, size_t size) {
    // Ensure the data is not NULL and has a minimum size
    if (data == NULL || size == 0) {
        return 0;
    }

    // Call the function-under-test
    // We cast the data to a void pointer as required by the function signature
    bool result = icalcomponent_isa_component((const void *)data);

    // Use the result in some way to avoid compiler optimizations removing the call
    volatile bool use_result = result;
    (void)use_result;

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

    LLVMFuzzerTestOneInput_958(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
