#include "libical/ical.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
    // Ensure there's enough data to work with
    if (size == 0) {
        return 0;
    }

    // Initialize an icalcomponent from the input data
    char *ical_string = (char *)malloc(size + 1);
    if (!ical_string) {
        return 0;
    }
    memcpy(ical_string, data, size);
    ical_string[size] = '\0';

    icalcomponent *component = icalparser_parse_string(ical_string);
    free(ical_string);

    // Ensure the component is not NULL
    if (component == NULL) {
        return 0;
    }

    // Initialize the iterator
    icalcompiter iter = icalcomponent_begin_component(component, ICAL_ANY_COMPONENT);

    // Call the function-under-test
    icalcomponent *prior_component = icalcompiter_prior(&iter);

    // Clean up
    if (component != NULL) {
        icalcomponent_free(component);
    }

    return 0;
}