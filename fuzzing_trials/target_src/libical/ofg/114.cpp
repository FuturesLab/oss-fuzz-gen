#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_114(const uint8_t *data, size_t size) {
    // Initialize icalcomponent and icaltimetype
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    struct icaltimetype dtstart;

    // Ensure the data is large enough to extract a date-time value
    if (size >= 8) {
        // Extract year, month, day, hour, minute, second from the data
        int year = (int)((data[0] << 8) | data[1]);
        int month = (int)(data[2] % 12 + 1); // Ensure month is between 1 and 12
        int day = (int)(data[3] % 31 + 1);   // Ensure day is between 1 and 31
        int hour = (int)(data[4] % 24);      // Ensure hour is between 0 and 23
        int minute = (int)(data[5] % 60);    // Ensure minute is between 0 and 59
        int second = (int)(data[6] % 60);    // Ensure second is between 0 and 59

        // Initialize the icaltimetype with extracted values
        dtstart = icaltime_from_timet_with_zone(time(NULL), 0, NULL);
        dtstart.year = year;
        dtstart.month = month;
        dtstart.day = day;
        dtstart.hour = hour;
        dtstart.minute = minute;
        dtstart.second = second;

        // Call the function-under-test
        icalcomponent_set_dtstart(component, dtstart);
    }

    // Clean up
    icalcomponent_free(component);

    return 0;
}