#include <iostream>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_160(const uint8_t *data, size_t size) {
    // Initialize the library context
    icalcomponent *component = nullptr;
    icalproperty_kind kind = ICAL_ANY_PROPERTY;

    // Create a dummy icalcomponent to pass to the function
    component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == nullptr) {
        return 0; // Early exit if component creation fails
    }

    // Iterate over a few icalproperty_kinds to test the function
    icalpropiter iter;
    iter = icalcomponent_begin_property(component, kind);
    iter = icalcomponent_begin_property(component, ICAL_SUMMARY_PROPERTY);
    iter = icalcomponent_begin_property(component, ICAL_DTSTART_PROPERTY);
    iter = icalcomponent_begin_property(component, ICAL_DTEND_PROPERTY);

    // Clean up
    if (component != nullptr) {
        icalcomponent_free(component);
    }

    return 0;
}