#include <libical/ical.h>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>

extern "C" int LLVMFuzzerTestOneInput_541(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated and non-empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the null-terminated string
    char *name = new char[size + 1];
    std::memcpy(name, data, size);
    name[size] = '\0';

    // Validate the input before using it to create a property
    if (icalproperty_kind_is_valid(icalproperty_string_to_kind(name))) {
        // Call the function-under-test
        icalproperty *property = icalproperty_new_name(name);

        // Clean up
        if (property != nullptr) {
            icalproperty_free(property);
        }
    }

    delete[] name;

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

    LLVMFuzzerTestOneInput_541(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
