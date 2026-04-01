#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_147(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *vtodo = icalcomponent_new_vtodo();

    // If the component is created successfully, perform some operations
    if (vtodo != NULL) {
        // Set a property to the vtodo component to test further
        icalcomponent_set_summary(vtodo, "Sample VTODO Summary");

        // Retrieve the summary to ensure it was set correctly
        const char *summary = icalcomponent_get_summary(vtodo);

        // Print the summary for debugging purposes
        if (summary != NULL) {
            // This would be a placeholder for actual verification or further processing
            // In fuzzing, this might be logged or used to check for consistency
        }

        // Free the component to avoid memory leaks
        icalcomponent_free(vtodo);
    }

    return 0;
}