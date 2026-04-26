#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_1266(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a valid string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *inputStr = (char *)malloc(size + 1);
    if (inputStr == nullptr) {
        return 0;
    }
    memcpy(inputStr, data, size);
    inputStr[size] = '\0';

    // Create an icalproperty object using the input string
    icalproperty *property = icalproperty_new_from_string(inputStr);
    if (property != nullptr) {
        // Call the function-under-test
        const char *description = icalproperty_get_description(property);

        // Use the description in some way to avoid compiler optimizations
        if (description != nullptr) {
            // For fuzzing purposes, we don't need to do anything with the description
        }

        // Clean up
        icalproperty_free(property);
    }

    // Free allocated memory
    free(inputStr);

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

    LLVMFuzzerTestOneInput_1266(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
