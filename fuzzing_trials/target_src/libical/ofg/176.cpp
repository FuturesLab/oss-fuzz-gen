#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_176(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_vevent();

    // Check if the component is created successfully
    if (component != NULL) {
        // Perform operations on the component if necessary
        // For example, you can add properties or manipulate the component
        // Here, we simply free the component to avoid memory leaks
        icalcomponent_free(component);
    }

    return 0;
}