#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a string from the input data
    char *ical_string = (char *)malloc(size + 1);
    if (ical_string == NULL) {
        return 0;
    }
    memcpy(ical_string, data, size);
    ical_string[size] = '\0';

    // Parse the string into an icalcomponent
    icalcomponent *component = icalparser_parse_string(ical_string);
    free(ical_string);

    // Ensure that the component is not NULL
    if (component == NULL) {
        return 0;
    }

    // Initialize the icalcomponent_kind
    icalcomponent_kind kind = icalcomponent_isa(component);

    // Call the function-under-test
    icalcompiter iter = icalcomponent_begin_component(component, kind);

    // Clean up
    icalcomponent_free(component);

    return 0;
}