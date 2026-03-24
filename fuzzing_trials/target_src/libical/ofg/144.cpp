#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_144(const uint8_t *data, size_t size) {
    // Initialize an icalcomponent
    icalcomponent *parent_component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);

    // Add a subcomponent to ensure there is at least one component to retrieve
    icalcomponent *sub_component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalcomponent_add_component(parent_component, sub_component);

    // Define an icalcomponent_kind
    icalcomponent_kind kind = ICAL_VEVENT_COMPONENT;

    // Call the function-under-test
    icalcomponent *result = icalcomponent_get_first_component(parent_component, kind);

    // Clean up
    icalcomponent_free(parent_component);

    return 0;
}