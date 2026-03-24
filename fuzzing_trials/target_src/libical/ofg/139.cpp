#include <cstdint>  // Include for uint8_t
#include <cstdio>   // Include for printf

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_139(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_vquery();

    // Check if the component is created successfully
    if (component != NULL) {
        // Perform operations on the component if needed
        // For example, convert the component to a string and print it
        char *component_str = icalcomponent_as_ical_string(component);
        if (component_str != NULL) {
            // Print the component string
            printf("%s\n", component_str);
        }

        // Free the component
        icalcomponent_free(component);
    }

    return 0;
}