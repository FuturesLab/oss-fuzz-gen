#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream> // For debugging purposes

extern "C" int LLVMFuzzerTestOneInput_145(const uint8_t *data, size_t size) {
    // Ensure the input data is non-empty and of a reasonable size
    if (size == 0 || size > 1000) { // Limit size to prevent excessive allocation
        return 0;
    }

    // Create a null-terminated string from the input data
    char *inputStr = (char *)malloc(size + 1);
    if (inputStr == NULL) {
        return 0;
    }
    memcpy(inputStr, data, size);
    inputStr[size] = '\0';

    // Debugging: Print the input to check its content
    std::cout << "Input: " << inputStr << std::endl;

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_recuraccepted(inputStr);

    // Check if the property was created successfully
    if (prop != NULL) {
        // Further operations can be done here to increase coverage
        // For example, serialize the property or extract information
        icalproperty_free(prop);
    }

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

    LLVMFuzzerTestOneInput_145(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
