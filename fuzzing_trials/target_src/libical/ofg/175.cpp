#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_175(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract meaningful values
    if (size < sizeof(int) * 6) {
        return 0;
    }

    // Initialize an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Extract values for icaltimetype from the data
    int year = (int)data[0] + 1900; // Year starting from 1900
    int month = (int)data[1] % 12 + 1; // Month between 1 and 12
    int day = (int)data[2] % 31 + 1; // Day between 1 and 31
    int hour = (int)data[3] % 24; // Hour between 0 and 23
    int minute = (int)data[4] % 60; // Minute between 0 and 59
    int second = (int)data[5] % 60; // Second between 0 and 59

    // Create an icaltimetype
    struct icaltimetype dtstamp = icaltime_from_string("19700101T000000Z");
    dtstamp.year = year;
    dtstamp.month = month;
    dtstamp.day = day;
    dtstamp.hour = hour;
    dtstamp.minute = minute;
    dtstamp.second = second;

    // Call the function-under-test
    icalcomponent_set_dtstamp(component, dtstamp);

    // Clean up
    icalcomponent_free(component);

    return 0;
}