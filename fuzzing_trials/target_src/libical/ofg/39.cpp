#include <libical/ical.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_39(const uint8_t *data, size_t size) {
    // Create a new icalcomponent for the parent
    icalcomponent *parent_component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    
    // Create a new icalcomponent for the child
    icalcomponent *child_component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Add the child component to the parent component
    icalcomponent_add_component(parent_component, child_component);

    // Call the function under test
    icalcomponent_remove_component(parent_component, child_component);

    // Clean up
    icalcomponent_free(parent_component);
    // No need to free child_component as it's managed by the parent

    return 0;
}