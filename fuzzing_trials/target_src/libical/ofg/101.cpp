#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_101(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_xdaylight();

    // Perform basic operations on the component to ensure it is utilized
    if (component != NULL) {
        // Convert the component to a string and back to ensure functionality
        char *component_str = icalcomponent_as_ical_string(component);
        if (component_str != NULL) {
            icalcomponent *parsed_component = icalparser_parse_string(component_str);
            if (parsed_component != NULL) {
                // Clean up the parsed component
                icalcomponent_free(parsed_component);
            }
            // Free the string representation
            icalmemory_free_buffer(component_str);
        }

        // Free the original component
        icalcomponent_free(component);
    }

    return 0;
}