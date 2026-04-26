#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h> // Correct path for libical headers
}

extern "C" int LLVMFuzzerTestOneInput_1258(const uint8_t *data, size_t size) {
    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a dummy icalproperty object
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);

    // Ensure the property is not NULL
    if (property == NULL) {
        return 0;
    }

    // Set a value to the property using the input data
    // Convert the input data to a string
    char *value = (char *)malloc(size + 1);
    if (value == NULL) {
        icalproperty_free(property);
        return 0;
    }
    memcpy(value, data, size);
    value[size] = '\0';

    // Set the string value to the property
    icalproperty_set_value(property, icalvalue_new_string(value));

    // Call additional functions to increase code coverage
    // Serialize the property to a string
    const char *property_as_string = icalproperty_as_ical_string(property);
    if (property_as_string != NULL) {
        // Parse the string back to a property to test parsing logic
        icalproperty *parsed_property = icalproperty_new_from_string(property_as_string);
        if (parsed_property != NULL) {
            // Perform some operations on the parsed property
            icalproperty_set_x_name(parsed_property, "X-TEST");
            icalproperty_free(parsed_property);
        }
    }

    // Free allocated resources
    free(value);
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

    LLVMFuzzerTestOneInput_1258(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
