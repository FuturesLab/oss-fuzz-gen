#include <cstdint>  // Include for uint8_t
#include <cstdio>   // Include for printf

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_138(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_vavailability();

    // Check if the component is created successfully
    if (component != NULL) {
        // Perform some operations on the component
        // For example, convert the component to a string and print it
        char *component_str = icalcomponent_as_ical_string(component);
        if (component_str != NULL) {
            // Print the component string (for debugging purposes)
            // In a real fuzzing scenario, you might want to do more complex operations
            printf("%s\n", component_str);
        }

        // Free the component after use
        icalcomponent_free(component);
    }

    return 0;
}