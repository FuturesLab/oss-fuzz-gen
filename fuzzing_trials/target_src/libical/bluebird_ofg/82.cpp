#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy

extern "C" {
    #include "libical/ical.h"  // Corrected include path for libical
}

extern "C" int LLVMFuzzerTestOneInput_82(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract meaningful values
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Extract a struct icaltimetype from the input data
    struct icaltimetype recurrence_id;
    memcpy(&recurrence_id, data, sizeof(struct icaltimetype));

    // Ensure the struct icaltimetype is valid by setting some fields
    recurrence_id.year = 2023;  // Example year
    recurrence_id.month = 10;   // Example month
    recurrence_id.day = 31;     // Example day
    recurrence_id.hour = 12;    // Example hour
    recurrence_id.minute = 0;   // Example minute
    recurrence_id.second = 0;   // Example second
    recurrence_id.is_date = 0;  // Not a date-only value

    // Set a valid timezone to avoid crashes related to timezone issues
    icaltimezone *timezone = icaltimezone_get_builtin_timezone("UTC");
    if (timezone == NULL) {
        icalcomponent_free(component);
        return 0;
    }
    recurrence_id.zone = timezone;

    // Call the function-under-test
    icalcomponent_set_recurrenceid(component, recurrence_id);

    // Clean up
    icalcomponent_free(component);

    return 0;
}