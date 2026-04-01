#include <stdint.h>
#include <stdlib.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_67(const uint8_t *data, size_t size) {
    // Initialize the icalproperty and icalcomponent
    icalproperty *property = icalproperty_new_comment("Test Comment");
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);

    // Ensure the data is not NULL and size is sufficient
    if (property != NULL && component != NULL && size > 0) {
        // Call the function-under-test
        icalproperty_set_parent(property, component);
    }

    // Clean up
    if (property != NULL) {
        icalproperty_free(property);
    }
    if (component != NULL) {
        icalcomponent_free(component);
    }

    return 0;
}