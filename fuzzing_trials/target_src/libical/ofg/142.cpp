#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    // Include necessary C headers and function declarations
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_142(const uint8_t *data, size_t size) {
    // Initialize variables
    icalcomponent *component = nullptr;
    char *timezone_name = nullptr;

    // Ensure size is sufficient for a null-terminated string
    if (size < 1) return 0;

    // Allocate memory for the timezone name and copy data
    timezone_name = (char *)malloc(size + 1);
    if (timezone_name == nullptr) return 0;
    memcpy(timezone_name, data, size);
    timezone_name[size] = '\0'; // Null-terminate the string

    // Create a dummy icalcomponent for testing
    component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    if (component == nullptr) {
        free(timezone_name);
        return 0;
    }

    // Add a dummy VEVENT to the VCALENDAR to ensure there's content to process
    icalcomponent *event = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (event != nullptr) {
        icalcomponent_add_component(component, event);
    }

    // Call the function-under-test
    icaltimezone *timezone = icalcomponent_get_timezone(component, timezone_name);

    // Check if the timezone is not null to ensure the function is processing inputs
    if (timezone != nullptr) {
        // Optionally perform operations with the timezone to ensure code coverage
        const char *tzid = icaltimezone_get_location(timezone);
        if (tzid != nullptr) {
            // Use the tzid to do something meaningful
        }
    }

    // Clean up
    icalcomponent_free(component);
    free(timezone_name);

    return 0;
}