#include <libical/ical.h>
#include <stddef.h>
#include <stdint.h>

extern "C" int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to create a valid icalcomponent
    if (size < 1) {
        return 0;
    }

    // Create a dummy icalcomponent for testing
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Create an icalcompiter
    icalcompiter iter = icalcomponent_begin_component(component, ICAL_ANY_COMPONENT);

    // Call the function-under-test
    icalcomponent *result = icalcompiter_prior(&iter);

    // Clean up
    icalcomponent_free(component);

    return 0;
}