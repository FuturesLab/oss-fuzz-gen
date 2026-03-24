#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_70(const uint8_t *data, size_t size) {
    // Ensure the size is large enough to create a component and property kind
    if (size < 2) {
        return 0;
    }

    // Create a dummy icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Use the first byte of data to determine the property kind
    icalproperty_kind kind = static_cast<icalproperty_kind>(data[0] % ICAL_NO_PROPERTY);

    // Call the function-under-test
    icalproperty *property = icalcomponent_get_first_property(component, kind);

    // Clean up
    if (property != NULL) {
        icalproperty_free(property);
    }
    icalcomponent_free(component);

    return 0;
}