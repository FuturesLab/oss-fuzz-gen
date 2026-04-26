#include <cstdint>
#include <cstdlib>
#include <cstring>  // Include the C library for memcpy

// Assuming the function is part of a C library, we wrap it in extern "C"
extern "C" {
    char *icalproperty_enum_to_string_r(int);
}

extern "C" int LLVMFuzzerTestOneInput_1185(const uint8_t *data, size_t size) {
    // Check if size is at least the size of an int
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int input_value;
    std::memcpy(&input_value, data, sizeof(int));

    // Call the function-under-test
    char *result = icalproperty_enum_to_string_r(input_value);

    // Normally, you would do something with the result, but since this is a fuzz test,
    // we are only interested in whether the function can handle the input without crashing.
    // If the result needs to be freed or handled in a specific way, do so here.

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

    LLVMFuzzerTestOneInput_1185(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
