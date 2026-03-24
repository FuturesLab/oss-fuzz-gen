#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_115(const uint8_t *data, size_t size) {
    // Initialize an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Ensure size is sufficient to extract a meaningful year, month, day, etc.
    if (size < 6) {
        icalcomponent_free(component);
        return 0;
    }

    // Create an icaltimetype from the input data
    struct icaltimetype dtstart;
    dtstart.year = 1900 + (int)data[0]; // Year range: 1900-2055
    dtstart.month = (int)data[1] % 12 + 1; // Month range: 1-12
    dtstart.day = (int)data[2] % 31 + 1; // Day range: 1-31
    dtstart.hour = (int)data[3] % 24; // Hour range: 0-23
    dtstart.minute = (int)data[4] % 60; // Minute range: 0-59
    dtstart.second = (int)data[5] % 60; // Second range: 0-59
    dtstart.is_date = 0; // Set to 0 for date-time
    dtstart.zone = icaltimezone_get_utc_timezone(); // Use UTC timezone

    // Call the function-under-test
    icalcomponent_set_dtstart(component, dtstart);

    // Clean up
    icalcomponent_free(component);

    return 0;
}