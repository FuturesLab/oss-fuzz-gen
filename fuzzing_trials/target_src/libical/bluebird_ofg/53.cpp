#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
    // Ensure data is null-terminated for string operations
    if (size == 0) {
        return 0;
    }

    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0;
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Create a new icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        free(null_terminated_data);
        return 0;
    }

    // Call the function-under-test
    icalcomponent_set_relcalid(component, null_terminated_data);

    // Additional operations to ensure code coverage
    icalproperty *prop = icalproperty_new_relcalid(null_terminated_data);
    if (prop != NULL) {
        icalcomponent_add_property(component, prop);
    }

    // To increase code coverage, attempt to manipulate the component further
    icalcomponent *clone = icalcomponent_clone(component);
    if (clone != NULL) {
        icalcomponent_free(clone);
    }

    // Attempt to retrieve properties and trigger more code paths
    icalproperty *retrieved_prop = icalcomponent_get_first_property(component, ICAL_RELCALID_PROPERTY);
    if (retrieved_prop != NULL) {
        const char *retrieved_value = icalproperty_get_relcalid(retrieved_prop);
        if (retrieved_value != NULL) {
            // Do something with retrieved_value if needed
        }
    }

    // Clean up
    icalcomponent_free(component);
    free(null_terminated_data);

    return 0;
}