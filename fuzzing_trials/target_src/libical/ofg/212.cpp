#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // For malloc and free
#include <string.h>  // For memcpy

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
}

extern "C" int LLVMFuzzerTestOneInput_212(const uint8_t *data, size_t size) {
    // Ensure that the size is large enough to create a valid icalproperty
    if (size < 1) {
        return 0;
    }

    // Create a string from the input data to use as the property value
    char *property_value = (char *)malloc(size + 1);
    if (!property_value) {
        return 0;
    }
    memcpy(property_value, data, size);
    property_value[size] = '\0';

    // Create a new icalproperty from the input data
    icalproperty *property = icalproperty_new_from_string(property_value);
    free(property_value);

    if (!property) {
        return 0;
    }

    // Iterate over all possible icalparameter_kind values
    for (int kind = ICAL_ANY_PARAMETER; kind <= ICAL_X_PARAMETER; ++kind) {
        icalparameter_kind param_kind = static_cast<icalparameter_kind>(kind);

        // Call the function-under-test
        icalparameter *parameter = icalproperty_get_first_parameter(property, param_kind);

        // Optionally, perform some basic checks or operations on the parameter
        if (parameter) {
            // Example operation: get the kind of the parameter
            icalparameter_kind kind_check = icalparameter_isa(parameter);
        }
    }

    // Clean up
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

    LLVMFuzzerTestOneInput_212(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
