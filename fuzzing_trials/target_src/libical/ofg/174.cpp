#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_174(const uint8_t *data, size_t size) {
    // Ensure there is enough data to initialize icaltimetype
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Initialize an icaltimetype from the input data
    struct icaltimetype dtstamp;
    dtstamp.year = (int)(data[0] % 10000); // Ensure year is a valid value
    dtstamp.month = (int)((data[1] % 12) + 1); // Month is 1-12
    dtstamp.day = (int)((data[2] % 31) + 1); // Day is 1-31
    dtstamp.hour = (int)(data[3] % 24); // Hour is 0-23
    dtstamp.minute = (int)(data[4] % 60); // Minute is 0-59
    dtstamp.second = (int)(data[5] % 60); // Second is 0-59
    dtstamp.is_date = 0; // Set to 0 for date-time
    dtstamp.zone = icaltimezone_get_utc_timezone(); // Set to UTC timezone

    // Call the function under test
    icalcomponent_set_dtstamp(component, dtstamp);

    // Clean up
    icalcomponent_free(component);

    return 0;
}