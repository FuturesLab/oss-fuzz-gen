#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // For malloc and free
#include <string.h>  // For memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_158(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < 1) {
        return 0;
    }

    // Convert the input data to a string
    char *ical_string = (char *)malloc(size + 1);
    if (ical_string == NULL) {
        return 0;
    }
    memcpy(ical_string, data, size);
    ical_string[size] = '\0';

    // Parse the input data as an iCalendar component
    icalcomponent *component = icalparser_parse_string(ical_string);
    free(ical_string);

    if (component == NULL) {
        return 0;
    }

    // Initialize the icalpropiter
    icalproperty_kind kind = ICAL_ANY_PROPERTY;
    icalproperty *result = NULL;
    for (icalproperty *prop = icalcomponent_get_first_property(component, kind);
         prop != NULL;
         prop = icalcomponent_get_next_property(component, kind)) {
        result = prop;  // Use the property in some way
    }

    // Clean up
    icalcomponent_free(component);

    return 0;
}