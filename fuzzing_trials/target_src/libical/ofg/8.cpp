#include <libical/ical.h>
#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to create a null-terminated string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *str_data = new char[size + 1];
    memcpy(str_data, data, size);
    str_data[size] = '\0';

    // Call the function-under-test
    icalproperty *prop = icalproperty_vanew_xlicmimeoptinfo(str_data, nullptr);

    // Additional operations to increase code coverage
    if (prop != nullptr) {
        // Access some properties of the created icalproperty to increase coverage
        icalproperty_kind kind = icalproperty_isa(prop);
        const char *name = icalproperty_get_xlicmimeoptinfo(prop);
        
        // Use the retrieved information in some way
        if (kind == ICAL_XLICMIMEOPTINFO_PROPERTY && name != nullptr) {
            // Do something with the name, e.g., check its length
            size_t name_length = strlen(name);
            if (name_length > 0) {
                // Simulate further processing
            }
        }

        // Clean up
        icalproperty_free(prop);
    }

    delete[] str_data;

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

    LLVMFuzzerTestOneInput_8(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
