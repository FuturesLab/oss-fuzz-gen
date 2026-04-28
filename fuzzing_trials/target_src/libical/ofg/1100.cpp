#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream> // For debugging purposes

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1100(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for a null-terminated string
    if (size < 1) return 0;

    // Allocate memory for the string and ensure it's null-terminated
    char *patchversion_str = new char[size + 1];
    std::memcpy(patchversion_str, data, size);
    patchversion_str[size] = '\0';

    // Debug: Print the input being tested
    std::cout << "Testing input: " << patchversion_str << std::endl;

    // Call the function-under-test with the string and a non-null void pointer
    // Add nullptr as a sentinel value for the variadic function
    icalproperty *property = icalproperty_vanew_patchversion(patchversion_str, nullptr);

    // Check if the property is created successfully
    if (property != nullptr) {
        // Debug: Print the property type
        std::cout << "Property created: " << icalproperty_as_ical_string(property) << std::endl;

        // Clean up resources
        icalproperty_free(property);
    } else {
        // Debug: Indicate that property creation failed
        std::cout << "Failed to create property for input: " << patchversion_str << std::endl;
    }

    delete[] patchversion_str;

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

    LLVMFuzzerTestOneInput_1100(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
