#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size) {
    // Convert input data to a string
    char *ical_string = (char *)malloc(size + 1);
    if (ical_string == NULL) {
        return 0;
    }
    memcpy(ical_string, data, size);
    ical_string[size] = '\0';

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(ical_string);
    free(ical_string);

    // Ensure the component is not NULL
    if (component == NULL) {
        return 0;
    }

    // Perform some operations on the component
    icalcomponent_kind kind = icalcomponent_isa(component);
    if (kind == ICAL_VEVENT_COMPONENT) {
        int sequence = icalcomponent_get_sequence(component);
        // Additional operations could be added here
    }

    // Clean up
    icalcomponent_free(component);

    return 0;
}