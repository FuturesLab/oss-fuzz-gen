#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    // Initialize two icalcomponent pointers
    icalcomponent *component1 = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalcomponent *component2 = icalcomponent_new(ICAL_VTODO_COMPONENT);

    // Ensure that the components are not NULL
    if (component1 == NULL || component2 == NULL) {
        if (component1 != NULL) {
            icalcomponent_free(component1);
        }
        if (component2 != NULL) {
            icalcomponent_free(component2);
        }
        return 0;
    }

    // Call the function-under-test
    icalcomponent_set_parent(component1, component2);

    // Clean up
    icalcomponent_free(component1);
    icalcomponent_free(component2);

    return 0;
}