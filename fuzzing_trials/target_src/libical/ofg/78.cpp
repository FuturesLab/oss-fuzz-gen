#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // For malloc and free
#include <string.h>  // For memcpy

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_78(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to be meaningful
    if (size < 1) {
        return 0;
    }

    // Create a temporary buffer to hold the data
    char *tempData = (char *)malloc(size + 1);
    if (tempData == NULL) {
        return 0;
    }

    // Copy data into the temporary buffer and null-terminate it
    memcpy(tempData, data, size);
    tempData[size] = '\0';

    // Parse the data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(tempData);

    // Ensure the component is not NULL before proceeding
    if (component != NULL) {
        // Fuzz different kinds of icalcomponent_kind
        icalcomponent_kind kinds[] = {
            ICAL_VEVENT_COMPONENT,
            ICAL_VTODO_COMPONENT,
            ICAL_VJOURNAL_COMPONENT,
            ICAL_VFREEBUSY_COMPONENT,
            ICAL_VTIMEZONE_COMPONENT,
            ICAL_XSTANDARD_COMPONENT,
            ICAL_XDAYLIGHT_COMPONENT,
            ICAL_X_COMPONENT,
            ICAL_VCALENDAR_COMPONENT,
            ICAL_VSCHEDULE_COMPONENT,
            ICAL_ANY_COMPONENT
        };

        // Iterate over the kinds and call the function-under-test
        for (size_t i = 0; i < sizeof(kinds) / sizeof(kinds[0]); ++i) {
            int count = icalcomponent_count_components(component, kinds[i]);
            (void)count; // Suppress unused variable warning
        }

        // Free the component after use
        icalcomponent_free(component);
    }

    // Free the temporary buffer
    free(tempData);

    return 0;
}