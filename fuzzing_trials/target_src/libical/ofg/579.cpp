#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_579(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a null-terminated string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for a null-terminated string
    char *error_string = (char *)malloc(size + 1);
    if (error_string == NULL) {
        return 0;
    }

    // Copy the input data into the string and null-terminate it
    memcpy(error_string, data, size);
    error_string[size] = '\0';

    // Call the function-under-test
    icalproperty *property = icalproperty_vanew_xlicerror(error_string, NULL);

    // Check if the property was created successfully
    if (property != NULL) {
        // Access some attributes to ensure the property is being used
        icalproperty_kind kind = icalproperty_isa(property);
        if (kind == ICAL_XLICERROR_PROPERTY) {
            const char *value = icalproperty_get_xlicerror(property);
            if (value != NULL) {
                // Simulate some usage of the value
                size_t value_length = strlen(value);
                if (value_length > 0) {
                    // To maximize fuzzing result, use the value in a meaningful way
                    // For example, parse it or perform operations that would trigger more code paths
                    // Here is a simple example of logging or further processing
                    printf("X-LIC-ERROR value: %s\n", value);
                }
            }
        }

        // Clean up
        icalproperty_free(property);
    }
    free(error_string);

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

    LLVMFuzzerTestOneInput_579(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
