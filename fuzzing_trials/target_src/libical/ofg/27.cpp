#include <cstdint>  // Include for uint8_t
#include <cstddef>  // Include for size_t
#include <cstring>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create a valid string
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *input = new char[size + 1];
    memcpy(input, data, size);
    input[size] = '\0';

    // Parse the input data as an iCalendar property
    icalproperty *prop = icalproperty_new_from_string(input);

    // If the property was successfully created, use it
    if (prop != nullptr) {
        // Perform some operations on the property
        // For example, check if empty properties are allowed
        bool allow_empty = icalproperty_get_allow_empty_properties();

        // Clean up
        icalproperty_free(prop);
    }

    // Clean up the allocated string
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

    LLVMFuzzerTestOneInput_27(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
