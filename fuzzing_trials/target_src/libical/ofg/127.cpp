#include <cstdint>
#include <cstddef>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_127(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_vfreebusy();

    // Perform operations on the component if needed
    if (component != NULL) {
        // Example operation: Convert component to string and print (for debugging purposes)
        char *component_str = icalcomponent_as_ical_string(component);
        if (component_str != NULL) {
            // Normally, you might log or further process the string
            // For this example, we will just free the string
            icalmemory_free_buffer(component_str);
        }

        // Free the component after use
        icalcomponent_free(component);
    }

    return 0;
}