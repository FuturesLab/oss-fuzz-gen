#include <cstdint>  // Include for uint8_t
#include <cstddef>  // Include for size_t
#include <cstring>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_117(const uint8_t *data, size_t size) {
    // Initialize the iCalendar library
    icalcomponent *parent_component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    icalcomponent *child_component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Ensure the components are not NULL
    if (parent_component == NULL || child_component == NULL) {
        if (parent_component != NULL) {
            icalcomponent_free(parent_component);
        }
        if (child_component != NULL) {
            icalcomponent_free(child_component);
        }
        return 0;
    }

    // Create a string from the input data
    char *input_data = (char *)malloc(size + 1);
    if (input_data == NULL) {
        icalcomponent_free(parent_component);
        icalcomponent_free(child_component);
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0';  // Null-terminate the string

    // Parse the input data into an icalcomponent
    icalcomponent *parsed_component = icalparser_parse_string(input_data);

    // If parsing is successful, add the parsed component to the parent
    if (parsed_component != NULL) {
        icalcomponent_add_component(parent_component, parsed_component);
    }

    // Clean up
    free(input_data);
    icalcomponent_free(parent_component);
    // Note: child_component and parsed_component are freed by icalcomponent_free(parent_component)

    return 0;
}