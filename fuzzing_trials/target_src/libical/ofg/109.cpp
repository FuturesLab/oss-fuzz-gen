#include <cstdint>
#include <cstdlib>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_109(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_vjournal();

    // Perform operations on the component if needed
    if (component != NULL) {
        // Example operation: print the component to a string
        char *str = icalcomponent_as_ical_string(component);
        if (str != NULL) {
            // Normally, you might want to do something with the string
            // For a fuzzing harness, we don't need to do anything specific
        }

        // Free the string if it was allocated
        if (str != NULL) {
            free(str);
        }

        // Free the component
        icalcomponent_free(component);
    }

    return 0;
}