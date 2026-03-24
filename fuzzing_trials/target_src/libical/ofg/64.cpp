#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    // Ensure the size is enough to create a valid icaldurationtype
    if (size < sizeof(int) * 6) {
        return 0;
    }

    // Create an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Initialize an icaldurationtype with data
    struct icaldurationtype duration;
    duration.is_neg = data[0] % 2; // Use the first byte for is_neg
    duration.weeks = data[1];      // Use the second byte for weeks
    duration.days = data[2];       // Use the third byte for days
    duration.hours = data[3];      // Use the fourth byte for hours
    duration.minutes = data[4];    // Use the fifth byte for minutes
    duration.seconds = data[5];    // Use the sixth byte for seconds

    // Call the function-under-test
    icalcomponent_set_duration(component, duration);

    // Clean up
    icalcomponent_free(component);

    return 0;
}