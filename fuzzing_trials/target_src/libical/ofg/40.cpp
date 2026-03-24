#include <cstdint>
#include <cstddef>

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    // Initialize the main component and subcomponent
    icalcomponent *main_component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    icalcomponent *sub_component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Ensure that the components are not NULL
    if (main_component == NULL || sub_component == NULL) {
        if (main_component != NULL) {
            icalcomponent_free(main_component);
        }
        if (sub_component != NULL) {
            icalcomponent_free(sub_component);
        }
        return 0;
    }

    // Add the subcomponent to the main component
    icalcomponent_add_component(main_component, sub_component);

    // Call the function-under-test
    icalcomponent_remove_component(main_component, sub_component);

    // Free the main component
    icalcomponent_free(main_component);

    return 0;
}