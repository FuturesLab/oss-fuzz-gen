#include <cstdint>  // Include for uint8_t
#include <cstddef>  // Include for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_126(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_vfreebusy();

    // Perform any additional operations with the component if necessary
    // For this fuzzing harness, we'll just ensure the component is not NULL
    if (component != NULL) {
        // We can perform further operations or checks on the component here
        // For example, we could convert it to a string and print it
        char *component_str = icalcomponent_as_ical_string(component);
        if (component_str != NULL) {
            // Normally, you might print or log the string, but for fuzzing, we just ensure it's not NULL
            // printf("%s\n", component_str);
        }

        // Free the string if it was allocated
        icalmemory_free_buffer(component_str);

        // Free the component after use
        icalcomponent_free(component);
    }

    return 0;
}