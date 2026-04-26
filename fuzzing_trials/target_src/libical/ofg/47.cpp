extern "C" {
    #include <libical/ical.h>
    #include <string.h> // Include the necessary header for memcpy
}

#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated
    char *input = new char[size + 1];
    if (size > 0) {
        memcpy(input, data, size);
    }
    input[size] = '\0';

    // Call the function-under-test
    icalproperty *property = icalproperty_new_from_string(input);

    // Clean up
    if (property != NULL) {
        icalproperty_free(property);
    }
    delete[] input;

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

    LLVMFuzzerTestOneInput_47(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
