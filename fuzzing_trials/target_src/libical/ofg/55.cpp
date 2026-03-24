#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    // Convert the input data to a string
    char *ical_string = (char *)malloc(size + 1);
    if (ical_string == NULL) {
        return 0;
    }
    memcpy(ical_string, data, size);
    ical_string[size] = '\0';

    // Parse the input data as an icalcomponent
    icalcomponent *component = icalparser_parse_string(ical_string);
    free(ical_string);

    if (component == NULL) {
        return 0;
    }

    // Select a component kind to search for
    icalcomponent_kind kind = ICAL_VEVENT_COMPONENT;

    // Call the function-under-test
    icalcomponent *next_component = icalcomponent_get_next_component(component, kind);

    // Cleanup
    icalcomponent_free(component);

    return 0;
}