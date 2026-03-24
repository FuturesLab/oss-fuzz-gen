#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    // Initialize two icalcomponent pointers
    icalcomponent *comp1 = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    icalcomponent *comp2 = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Ensure that the components are not NULL
    if (comp1 == NULL || comp2 == NULL) {
        if (comp1 != NULL) {
            icalcomponent_free(comp1);
        }
        if (comp2 != NULL) {
            icalcomponent_free(comp2);
        }
        return 0;
    }

    // Call the function-under-test
    icalcomponent_set_parent(comp1, comp2);

    // Free the components
    icalcomponent_free(comp1);
    icalcomponent_free(comp2);

    return 0;
}