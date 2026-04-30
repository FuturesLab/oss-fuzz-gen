#include <cstdint>
#include <cstdlib>
#include <cstring> // Include this for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    // Create a temporary buffer to store the input data as a string
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0'; // Null-terminate the string

    // Initialize an icalproperty object
    icalproperty *property = icalproperty_new_from_string(inputData);
    if (property != NULL) {
        // Call the function under test
        const char *description = icalproperty_get_styleddescription(property);

        // Optionally, you can add code to do something with 'description'
        // For example, checking its validity or printing it for debugging
        // However, since this is a fuzzing harness, we generally don't need to do anything with it

        // Free the icalproperty object
        icalproperty_free(property);
    }

    // Free the allocated input data
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

    LLVMFuzzerTestOneInput_64(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
