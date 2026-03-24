#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_vlocation();

    // Perform operations on the component if needed
    if (component != NULL) {
        // Example operation: convert component to string and print
        char *component_str = icalcomponent_as_ical_string(component);
        if (component_str != NULL) {
            // Normally, we would do something with the string, but for fuzzing, we just ensure it doesn't crash
            // printf("%s\n", component_str); // Uncomment for debugging purposes
        }

        // Clean up and free the component
        icalcomponent_free(component);
    }

    return 0;
}