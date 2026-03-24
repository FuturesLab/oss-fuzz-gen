#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "libical/ical.h"

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to be used as a string
    if (size < 1) {
        return 0;
    }

    // Allocate and initialize an icalcomponent with a valid type
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *x_name = (char *)malloc(size + 1);
    if (x_name == NULL) {
        icalcomponent_free(component);
        return 0;
    }
    memcpy(x_name, data, size);
    x_name[size] = '\0';

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_x(x_name);
    if (prop != NULL) {
        icalcomponent_add_property(component, prop);
    }

    // Perform additional operations to increase code coverage
    icalcomponent_get_first_property(component, ICAL_X_PROPERTY);

    // Try to retrieve and manipulate the property to increase coverage
    icalproperty *retrieved_prop = icalcomponent_get_first_property(component, ICAL_X_PROPERTY);
    if (retrieved_prop != NULL) {
        const char *retrieved_value = icalproperty_get_x(retrieved_prop);
        if (retrieved_value != NULL) {
            // Further manipulate or use the retrieved value
            icalproperty_set_x(retrieved_prop, retrieved_value);
        }
    }

    // Clean up
    icalcomponent_free(component);
    free(x_name);

    return 0;
}