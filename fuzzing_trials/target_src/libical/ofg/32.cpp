#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for creating a null-terminated string
    if (size == 0) {
        return 0;
    }

    // Create an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *uid = (char *)malloc(size + 1);
    if (uid == NULL) {
        icalcomponent_free(component);
        return 0;
    }
    memcpy(uid, data, size);
    uid[size] = '\0';

    // Call the function-under-test
    icalcomponent_set_uid(component, uid);

    // Additional operations to increase code coverage
    // Parse the component back to a string and then back to a component
    char *component_str = icalcomponent_as_ical_string(component);
    if (component_str != NULL) {
        icalcomponent *parsed_component = icalparser_parse_string(component_str);
        if (parsed_component != NULL) {
            // Perform operations on the parsed component
            icalcomponent_free(parsed_component);
        }
    }

    // Clean up
    free(uid);
    icalcomponent_free(component);

    return 0;
}