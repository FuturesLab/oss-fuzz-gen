#include <cstdint>
#include <cstdlib>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_69(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_vreply();

    // Perform some operations on the component, if needed
    if (component != NULL) {
        // Example operation: Convert the component to a string and print it
        char *component_str = icalcomponent_as_ical_string(component);
        if (component_str != NULL) {
            // Normally, you might want to do something with this string
            // For fuzzing purposes, we just ensure the function is called
        }

        // Free the allocated string
        icalmemory_free_buffer(component_str);

        // Free the component
        icalcomponent_free(component);
    }

    return 0;
}