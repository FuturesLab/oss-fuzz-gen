#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_297(const uint8_t *data, size_t size) {
    // Ensure the input data is non-empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for a null-terminated string
    char *inputStr = (char *)malloc(size + 1);
    if (!inputStr) {
        return 0;
    }

    // Copy the data to the string and null-terminate it
    memcpy(inputStr, data, size);
    inputStr[size] = '\0';

    // Call the function under test
    icalproperty *property = icalproperty_new_xlicclustercount(inputStr);

    // Check if the property was successfully created
    if (property != NULL) {
        // Perform additional operations to ensure code coverage
        icalproperty_kind kind = icalproperty_isa(property);
        const char *value = icalproperty_get_xlicclustercount(property);

        // Use the kind and value to simulate further processing
        if (kind == ICAL_XLICCLUSTERCOUNT_PROPERTY && value != NULL) {
            // Simulate some processing logic
            size_t len = strlen(value);
            if (len > 0) {
                // Just a dummy operation to utilize the value
                char *copy = (char *)malloc(len + 1);
                if (copy) {
                    strcpy(copy, value);
                    free(copy);
                }
            }
        }

        // Clean up
        icalproperty_free(property);
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

    LLVMFuzzerTestOneInput_297(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
