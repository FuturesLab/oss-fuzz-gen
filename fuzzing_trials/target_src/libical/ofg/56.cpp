#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Initialize a memory zone for the icalcomponent
    icalcomponent *parent_component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    icalcomponent *child_component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Add the child component to the parent component
    icalcomponent_add_component(parent_component, child_component);

    // Fuzz different kinds of icalcomponent_kind
    icalcomponent_kind kinds[] = {
        ICAL_NO_COMPONENT,
        ICAL_ANY_COMPONENT,
        ICAL_VEVENT_COMPONENT,
        ICAL_VTODO_COMPONENT,
        ICAL_VJOURNAL_COMPONENT,
        ICAL_VFREEBUSY_COMPONENT,
        ICAL_VTIMEZONE_COMPONENT,
        ICAL_XSTANDARD_COMPONENT,
        ICAL_XDAYLIGHT_COMPONENT,
        ICAL_VALARM_COMPONENT,
        ICAL_X_COMPONENT,
        ICAL_VCALENDAR_COMPONENT,
        ICAL_VSCHEDULE_COMPONENT,
        ICAL_VQUERY_COMPONENT,
        ICAL_VCAR_COMPONENT,
        ICAL_XLICINVALID_COMPONENT,
        ICAL_XLICMIMEPART_COMPONENT,
        ICAL_VAVAILABILITY_COMPONENT,
        ICAL_XAVAILABLE_COMPONENT,
        ICAL_VPOLL_COMPONENT,
        ICAL_VVOTER_COMPONENT
    };

    // Iterate over each kind and call the function-under-test
    for (size_t i = 0; i < sizeof(kinds) / sizeof(kinds[0]); ++i) {
        icalcomponent *next_component = icalcomponent_get_next_component(parent_component, kinds[i]);
        // Use the next_component in some way to prevent compiler optimizations from removing the call
        if (next_component != NULL) {
            // Perform some operation with next_component
            icalcomponent_get_uid(next_component);
        }
    }

    // Create an icalparser and parse the input data
    icalparser *parser = icalparser_new();
    if (parser) {
        char *input_data = (char *)malloc(size + 1);
        if (input_data) {
            memcpy(input_data, data, size);
            input_data[size] = '\0'; // Ensure null-termination

            // Define a line generator function
            auto line_gen_func = [](char *s, size_t size, void *d) -> char* {
                char *input = (char *)d;
                if (*input == '\0') return NULL; // End of input
                size_t len = strlen(input);
                if (len > size - 1) len = size - 1;
                memcpy(s, input, len);
                s[len] = '\0';
                return s;
            };

            // Parse using the line generator function
            icalparser_set_gen_data(parser, input_data);
            icalparser_parse(parser, line_gen_func);

            free(input_data);
        }
        icalparser_free(parser);
    }

    // Clean up
    icalcomponent_free(parent_component);

    return 0;
}