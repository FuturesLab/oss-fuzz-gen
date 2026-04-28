#include <libical/ical.h>
#include <cstdint>
#include <cstddef>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated and non-empty
    if (size == 0) {
        return 0;
    }

    // Create a buffer to hold the null-terminated string
    char *inputString = new char[size + 1];
    std::memcpy(inputString, data, size);
    inputString[size] = '\0';  // Null-terminate the string

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_from_string(inputString);

    // Check if the property was created successfully
    if (prop != NULL) {
        // Perform some operations on the property to increase code coverage
        icalproperty_kind kind = icalproperty_isa(prop);
        const char *value = icalproperty_get_value_as_string(prop);

        // Clean up
        icalproperty_free(prop);
    }

    delete[] inputString;

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

    LLVMFuzzerTestOneInput_22(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
