#include <cstddef>  // For size_t
#include <cstdint>  // For uint8_t
#include <cstring>  // For strlen

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_79(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_vpatch();

    // Perform some operations on the component to ensure it is utilized
    if (component != NULL) {
        // Convert the component to a string and print its size
        char *component_str = icalcomponent_as_ical_string(component);
        size_t component_str_size = component_str ? strlen(component_str) : 0;

        // Free the string representation of the component
        if (component_str != NULL) {
            icalmemory_free_buffer(component_str);
        }

        // Free the component itself
        icalcomponent_free(component);
    }

    return 0;
}