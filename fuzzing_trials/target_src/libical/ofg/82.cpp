#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_82(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_xavailable();

    // Check if the component is created successfully
    if (component != NULL) {
        // Perform some operations on the component
        // For example, convert it to a string and print (if needed)
        char *component_str = icalcomponent_as_ical_string(component);
        if (component_str != NULL) {
            // Normally, you might print or log the string here
            // printf("%s\n", component_str);
        }

        // Free the component after use
        icalcomponent_free(component);
    }

    return 0;
}