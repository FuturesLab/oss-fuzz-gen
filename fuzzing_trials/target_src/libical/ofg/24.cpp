#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent structure
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Ensure the component is not NULL
    if (component == NULL) {
        return 0;
    }

    // Call the function-under-test
    const char *component_name = icalcomponent_get_component_name(component);

    // Use the result to prevent compiler optimizations from removing the call
    if (component_name != NULL) {
        // Print the component name (for debugging purposes, can be removed)
        // printf("Component Name: %s\n", component_name);
    }

    // Clean up the component
    icalcomponent_free(component);

    return 0;
}