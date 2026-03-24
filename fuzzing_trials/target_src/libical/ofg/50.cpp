#include <cstdint>  // Include for uint8_t
#include <cstddef>  // Include for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_vpoll();

    // Perform operations on the component if needed
    if (component != NULL) {
        // For example, you can convert the component to a string and print it
        char *component_str = icalcomponent_as_ical_string(component);
        if (component_str != NULL) {
            // Normally you might do something with component_str
            // For this fuzzer, we will just free it
            icalmemory_free_buffer(component_str);
        }

        // Clean up by freeing the component
        icalcomponent_free(component);
    }

    return 0;
}