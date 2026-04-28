#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_712(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for a null-terminated string
    if (size < 1) return 0;

    // Create a null-terminated string from the input data
    char *inputString = new char[size + 1];
    memcpy(inputString, data, size);
    inputString[size] = '\0';

    // Call the function-under-test
    icalproperty *property = icalproperty_vanew_itipversion(inputString, nullptr);

    // Additional processing to ensure code coverage
    if (property != nullptr) {
        // Access some properties to ensure the object is being utilized
        icalproperty_kind kind = icalproperty_isa(property);
        if (kind == ICAL_ITIPVERSION_PROPERTY) {
            // Perform some operation if the property is of the expected kind
            const char *version = icalproperty_get_itipversion(property);
            if (version != nullptr) {
                // Use the version string in some way
                printf("iTIP Version: %s\n", version);
            }
        }
        icalproperty_free(property);
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

    LLVMFuzzerTestOneInput_712(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
