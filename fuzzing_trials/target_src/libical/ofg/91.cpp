#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_91(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_vcalendar();

    // Check if the component was created successfully
    if (component != NULL) {
        // Perform operations on the component if needed
        // For example, convert the component to a string and print it
        char *component_str = icalcomponent_as_ical_string(component);
        if (component_str != NULL) {
            // Print the component string (optional, for debugging purposes)
            // printf("%s\n", component_str);
        }

        // Free the component string if it was allocated
        icalmemory_free_buffer(component_str);

        // Free the component to avoid memory leaks
        icalcomponent_free(component);
    }

    return 0;
}