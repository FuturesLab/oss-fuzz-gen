#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_888(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to create a valid string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *inputData = static_cast<char *>(malloc(size + 1));
    if (inputData == nullptr) {
        return 0;
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Create an icalproperty from the input data
    icalproperty *prop = icalproperty_new_from_string(inputData);

    // Check if the property was created successfully
    if (prop != nullptr) {
        // Call the function-under-test
        const char *error = icalproperty_get_xlicerror(prop);

        // Optionally, print the error for debugging purposes
        if (error != nullptr) {
            std::cout << "X-LIC-ERROR: " << error << std::endl;
        }

        // Free the icalproperty
        icalproperty_free(prop);
    }

    // Free the allocated memory
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

    LLVMFuzzerTestOneInput_888(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
