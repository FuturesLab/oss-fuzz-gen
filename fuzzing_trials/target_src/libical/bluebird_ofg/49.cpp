#include <stdint.h>
#include <stddef.h>
#include "libical/ical.h"
#include <string.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    // Ensure that the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Copy the input data to a null-terminated string
    char *ical_data = (char *)malloc(size + 1);
    if (ical_data == NULL) {
        return 0;
    }
    memcpy(ical_data, data, size);
    ical_data[size] = '\0';

    // Parse the input data as an iCalendar component
    icalcomponent *component = icalparser_parse_string(ical_data);
    free(ical_data);

    // Check if parsing was successful
    if (component == NULL) {
        return 0;
    }

    // Perform operations on the component
    icalproperty *property = icalcomponent_get_first_property(component, ICAL_ANY_PROPERTY);
    while (property != NULL) {
        // Perform operations on the property
        icalvalue *value = icalproperty_get_value(property);
        if (value != NULL) {
            // Example operation: Get the string representation of the value
            const char *value_str = icalvalue_as_ical_string(value);
            if (value_str != NULL) {
                // Do something with value_str (e.g., log, analyze, etc.)
            }
        }
        property = icalcomponent_get_next_property(component, ICAL_ANY_PROPERTY);
    }

    // Clean up
    icalcomponent_free(component);

    return 0;
}