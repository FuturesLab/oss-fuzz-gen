extern "C" {
#include "libical/ical.h"
}

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>

extern "C" int LLVMFuzzerTestOneInput_584(const uint8_t *data, size_t size) {
    // Ensure the input data is non-empty
    if (size == 0) return 0;

    // Allocate memory for a null-terminated string
    char *input = (char *)malloc(size + 1);
    if (input == nullptr) return 0;

    // Copy the input data and null-terminate it
    memcpy(input, data, size);
    input[size] = '\0';

    // Check if the input is potentially valid for the function
    if (strstr(input, "POLL") == nullptr) {
        free(input);
        return 0;
    }

    // Call the function-under-test
    icalproperty *property = icalproperty_new_pollproperties(input);

    // Check if the function was invoked successfully
    if (property != nullptr) {
        std::cout << "Property created successfully." << std::endl;
        icalproperty_free(property);
    } else {
        std::cout << "Failed to create property." << std::endl;
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

    LLVMFuzzerTestOneInput_584(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
