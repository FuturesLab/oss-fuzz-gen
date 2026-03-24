#include <libical/ical.h>
#include <stddef.h>
#include <stdint.h>

extern "C" int LLVMFuzzerTestOneInput_89(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_vresource();

    // Perform operations on the component if necessary
    if (component != NULL) {
        // Example operation: Convert component to string and print it
        char *component_str = icalcomponent_as_ical_string(component);
        if (component_str != NULL) {
            // Normally, you might do something with the string, like logging
            // Here we'll just ensure it doesn't crash
        }

        // Free the component after use
        icalcomponent_free(component);
    }

    return 0;
}