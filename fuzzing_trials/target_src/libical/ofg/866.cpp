#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_866(const uint8_t *data, size_t size) {
    // Initialize the icalproperty object
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);

    // Ensure the data is not empty
    if (size > 0) {
        // Create a string from the input data
        char *input_string = (char *)malloc(size + 1);
        if (input_string == NULL) {
            return 0; // Memory allocation failed
        }
        memcpy(input_string, data, size);
        input_string[size] = '\0';

        // Set the value of the property
        icalvalue *value = icalvalue_new_from_string(ICAL_ANY_VALUE, input_string);
        if (value != NULL) {
            icalproperty_set_value(property, value);
        }

        free(input_string);
    }

    // Call the function-under-test
    char *result = icalproperty_get_value_as_string_r(property);

    // Free allocated resources
    if (result != NULL) {
        free(result);
    }
    icalproperty_free(property);

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

    LLVMFuzzerTestOneInput_866(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
