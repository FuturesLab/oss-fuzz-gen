#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    // Initialize an icalcomponent object
    icalcomponent *comp = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Define an icalcomponent_kind variable
    icalcomponent_kind kind = ICAL_VEVENT_COMPONENT;

    // Ensure the data is not empty
    if (size > 0) {
        // Use the data to modify the component or kind in some way
        // For simplicity, let's assume the first byte determines the kind
        kind = static_cast<icalcomponent_kind>(data[0] % ICAL_NO_COMPONENT);
    }

    // Call the function-under-test
    icalcompiter iter = icalcomponent_begin_component(comp, kind);

    // Clean up
    icalcomponent_free(comp);

    return 0;
}