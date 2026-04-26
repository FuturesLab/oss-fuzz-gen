#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_354(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to be a valid string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *inputData = static_cast<char*>(malloc(size + 1));
    if (inputData == nullptr) {
        return 0; // Memory allocation failed
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Create a new icalproperty object
    icalproperty *property = icalproperty_new_from_string(inputData);
    if (property != nullptr) {
        // Call the function-under-test
        const char *result = icalproperty_get_xlicclustercount(property);

        // Use the result in some way to avoid compiler optimizations removing the call
        if (result != nullptr) {
            // For fuzzing purposes, we don't need to do anything with the result
        }

        // Clean up
        icalproperty_free(property);
    }

    free(inputData);
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

    LLVMFuzzerTestOneInput_354(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
