#include <cstdint> // Include for uint8_t
#include <cstdlib> // Include for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_vtimezone();

    // Check if the component is created successfully
    if (component != NULL) {
        // Optionally, you can perform some operations on the component
        // For example, convert it to a string and print (if needed for debugging)
        char *component_str = icalcomponent_as_ical_string(component);
        if (component_str != NULL) {
            // Print the component string (for debugging purposes)
            // printf("%s\n", component_str);
        }

        // Free the component string if it was allocated
        if (component_str != NULL) {
            icalmemory_free_buffer(component_str);
        }

        // Free the component after use
        icalcomponent_free(component);
    }

    return 0;
}