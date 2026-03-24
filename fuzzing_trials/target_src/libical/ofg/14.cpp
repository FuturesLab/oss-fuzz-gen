#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_xstandard();

    // Perform operations on the component if necessary
    if (component != NULL) {
        // Example operation: Convert the component to a string and print it
        char *component_str = icalcomponent_as_ical_string(component);
        if (component_str != NULL) {
            // Normally, you would do something with the string, like logging or further processing
            // For the purpose of this fuzzing harness, we'll just free the string
            icalmemory_free_buffer(component_str);
        }

        // Free the component after use
        icalcomponent_free(component);
    }

    return 0;
}