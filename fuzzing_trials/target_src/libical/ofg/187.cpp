#include <stdint.h>
#include <stdlib.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_187(const uint8_t *data, size_t size) {
    // Initialize an icalcomponent object
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Ensure the component has some data to work with
    icalcomponent_set_uid(component, "test-uid");
    icalcomponent_set_summary(component, "Test Event");

    // Call the function-under-test
    icalcomponent_free(component);

    return 0;
}