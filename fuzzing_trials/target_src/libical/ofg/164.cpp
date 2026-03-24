#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_164(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create an icalproperty
    if (size < 1) {
        return 0;
    }

    // Create a dummy icalproperty
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Initialize an icalproperty_kind
    icalproperty_kind kind = icalproperty_isa(property);

    // Create a string from the input data
    char *input_str = (char *)malloc(size + 1);
    if (input_str == NULL) {
        icalproperty_free(property);
        return 0;
    }
    memcpy(input_str, data, size);
    input_str[size] = '\0';

    // Convert icalproperty_kind to icalvalue_kind
    icalvalue_kind value_kind = ICAL_NO_VALUE;
    switch (kind) {
        case ICAL_ANY_PROPERTY:
            value_kind = ICAL_STRING_VALUE;
            break;
        // Add additional cases here for different property kinds if needed
        default:
            value_kind = ICAL_STRING_VALUE;
            break;
    }

    // Set the property value from input data
    icalvalue *value = icalvalue_new_from_string(value_kind, input_str);
    if (value != NULL) {
        icalproperty_set_value(property, value);
    }

    // Iterate over parameters instead of properties
    icalparameter *iter = icalproperty_get_first_parameter(property, ICAL_ANY_PARAMETER);

    // Call the function-under-test
    bool is_valid = (iter != NULL);

    // Cleanup
    free(input_str);
    icalproperty_free(property);

    return is_valid ? 1 : 0;
}