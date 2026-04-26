#include <libical/ical.h>
#include <cstdint>
#include <cstddef>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_423(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated
    if (size == 0) {
        return 0;
    }

    char *input = new char[size + 1];
    memcpy(input, data, size);
    input[size] = '\0';

    // Call the function-under-test
    icalproperty *property = icalproperty_new_restriction(input);

    // Additional operations to ensure code coverage
    if (property != NULL) {
        // Access some properties or methods to increase coverage
        icalproperty_kind kind = icalproperty_isa(property);
        const char *value = icalproperty_get_restriction(property);

        // Perform some basic checks
        if (kind == ICAL_RESTRICTION_PROPERTY && value != NULL) {
            // Use the value in some way
            size_t value_length = strlen(value);
            if (value_length > 0) {
                // Do something with value_length to ensure it's used
            }
        }

        // Clean up
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

    LLVMFuzzerTestOneInput_423(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
