#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_vpatch();

    // Check if the component is successfully created
    if (component != NULL) {
        // Perform operations on the component if needed
        // For example, convert it to a string and print it
        char *str = icalcomponent_as_ical_string(component);
        if (str != NULL) {
            // Normally, you might use the string here
            // For fuzzing, we just want to ensure it doesn't crash
        }

        // Free the component after use
        icalcomponent_free(component);
    }

    return 0;
}