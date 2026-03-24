#include <libical/ical.h>
#include <cstddef>
#include <cstdint>

// Ensure C linkage for the function-under-test
extern "C" {
    char *icalcomponent_get_component_name_r(const icalcomponent *);
}

extern "C" int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
    // Create a temporary icalcomponent object
    icalcomponent *component = icalcomponent_new(ICAL_NO_COMPONENT);

    // Call the function-under-test ensuring the component is not NULL
    char *component_name = icalcomponent_get_component_name_r(component);

    // Free the allocated component
    icalcomponent_free(component);

    // Return 0 to indicate successful execution
    return 0;
}