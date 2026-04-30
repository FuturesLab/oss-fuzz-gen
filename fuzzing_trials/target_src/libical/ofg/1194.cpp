#include <cstdint>  // For uint8_t
#include <cstddef>  // For size_t
#include <cstdlib>  // For malloc and free
#include <cstring>  // For memcpy

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1194(const uint8_t *data, size_t size) {
    // Ensure the data has a null terminator to be used as a C string
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0;
    }

    memcpy(input, data, size);
    input[size] = '\0';

    // Call the function-under-test
    icalproperty *property = icalproperty_new_defaultvcars(input);

    // Clean up
    if (property != NULL) {
        icalproperty_free(property);
    }
    free(input);

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

    LLVMFuzzerTestOneInput_1194(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
