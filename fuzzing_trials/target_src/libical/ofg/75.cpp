#include <cstdint>  // Include for uint8_t
#include <cstddef>  // Include for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_75(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_vagenda();

    // Check if the component is created successfully
    if (component != NULL) {
        // Perform some operations on the component if needed
        // For example, convert it to a string and print (or just ensure it doesn't crash)
        char *component_str = icalcomponent_as_ical_string(component);
        if (component_str != NULL) {
            // Normally, you might print or log the string, but for fuzzing, we just ensure it doesn't crash
            // printf("%s\n", component_str);
        }

        // Free the component after use
        icalcomponent_free(component);
    }

    return 0;
}