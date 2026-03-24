#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_159(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to extract a property kind
    if (size < sizeof(icalproperty_kind)) {
        return 0;
    }

    // Create a new icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Extract a property kind from the input data
    icalproperty_kind prop_kind = static_cast<icalproperty_kind>(data[0]);

    // Call the function-under-test
    icalpropiter prop_iter = icalcomponent_begin_property(component, prop_kind);

    // Clean up
    icalcomponent_free(component);

    return 0;
}