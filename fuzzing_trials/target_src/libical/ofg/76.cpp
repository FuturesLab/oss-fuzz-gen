#include <cstdint>  // Include for uint8_t
#include <cstddef>  // Include for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_76(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_vagenda();

    // Check if the component was created successfully
    if (component != NULL) {
        // Perform any additional operations on the component if needed
        // For example, you could serialize the component to a string
        char *component_str = icalcomponent_as_ical_string(component);
        if (component_str != NULL) {
            // Normally, you might log or further process the string
            // For this fuzzing harness, we will just free it
            icalmemory_free_buffer(component_str);
        }

        // Free the component to avoid memory leaks
        icalcomponent_free(component);
    }

    return 0;
}