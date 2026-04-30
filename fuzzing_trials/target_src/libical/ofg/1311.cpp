#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

// Ensure compatibility between C and C++ linkage
extern "C" {
    icalproperty* icalproperty_new_grant(const char *);
    void icalproperty_free(icalproperty*);
}

extern "C" int LLVMFuzzerTestOneInput_1311(const uint8_t *data, size_t size) {
    // Ensure the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Ensure the input data is null-terminated before passing it as a string
    char *input = (char *)malloc(size + 1);
    if (input == nullptr) {
        return 0; // Exit if memory allocation fails
    }

    // Copy the data into the input buffer and null-terminate it
    memcpy(input, data, size);
    input[size] = '\0';

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_grant(input);

    // Check if the property was created successfully
    if (prop != nullptr) {
        // Perform additional operations on `prop` to increase coverage
        // For instance, inspecting or modifying properties
        // Example: Get and set a property value (if applicable)
        const char *value = icalproperty_get_grant(prop);
        if (value) {
            icalproperty_set_grant(prop, value);
        }

        // Clean up
        icalproperty_free(prop);
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

    LLVMFuzzerTestOneInput_1311(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
