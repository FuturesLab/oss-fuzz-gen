#include <cstdint>
#include <cstdlib>
#include <cstring> // Include this for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1055(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a valid string
    if (size < 1) return 0;

    // Allocate memory for the input string and ensure it's null-terminated
    char *inputStr = (char *)malloc(size + 1);
    if (inputStr == nullptr) return 0;
    memcpy(inputStr, data, size);
    inputStr[size] = '\0';

    // Create an icalproperty from the input string
    icalproperty *property = icalproperty_new_from_string(inputStr);

    // Free the input string as it's no longer needed
    free(inputStr);

    // If the property is successfully created, call the function-under-test
    if (property != nullptr) {
        const char *target = icalproperty_get_target(property);
        
        // Optionally, do something with the target, like logging or checking
        // For this harness, we simply call the function to test it

        // Clean up the icalproperty
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

    LLVMFuzzerTestOneInput_1055(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
