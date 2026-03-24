#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_177(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_vevent();

    // Perform operations on the component if necessary
    if (component != NULL) {
        // Example operation: Add a property to the component
        icalcomponent_add_property(component, icalproperty_new_summary("Sample Event"));

        // Example operation: Convert component to string
        char *component_str = icalcomponent_as_ical_string(component);

        // Free the component string if allocated
        if (component_str != NULL) {
            icalmemory_free_buffer(component_str);
        }

        // Free the component
        icalcomponent_free(component);
    }

    return 0;
}