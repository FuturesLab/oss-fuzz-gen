#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_642(const uint8_t *data, size_t size) {
    // Initialize the library if needed
    icalproperty *property = nullptr;

    // Ensure the size is sufficient to create a valid icalproperty
    if (size > 0) {
        // Create a new icalproperty from the input data
        // We use icalproperty_new_from_string to create a property from a string
        char *inputData = static_cast<char *>(malloc(size + 1));
        if (!inputData) {
            return 0;
        }
        memcpy(inputData, data, size);
        inputData[size] = '\0'; // Null-terminate the string

        property = icalproperty_new_from_string(inputData);
        free(inputData);
    }

    if (property != nullptr) {
        // Call the function-under-test
        const char *queryId = icalproperty_get_queryid(property);

        // Optionally, print the result for debugging purposes
        if (queryId != nullptr) {
            std::cout << "Query ID: " << queryId << std::endl;
        }

        // Free the icalproperty object
        icalproperty_free(property);
    }

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

    LLVMFuzzerTestOneInput_642(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
