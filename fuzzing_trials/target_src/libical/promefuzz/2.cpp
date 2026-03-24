// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalproperty_get_datetime_with_component at icalproperty.c:1050:21 in icalcomponent.h
// icalcomponent_get_dtstart at icalcomponent.c:1553:21 in icalcomponent.h
// icalcomponent_set_dtstart at icalcomponent.c:1533:6 in icalcomponent.h
// icalcomponent_get_due at icalcomponent.c:2613:21 in icalcomponent.h
// icalcomponent_get_duration at icalcomponent.c:1664:25 in icalcomponent.h
// icalcomponent_set_dtend at icalcomponent.c:1622:6 in icalcomponent.h
#include "ical.h"
#include <cstdint>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) {
        return 0; // Not enough data to proceed
    }

    // Initialize libical structures
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalproperty *property = icalproperty_new(ICAL_DTSTART_PROPERTY);

    // Prepare dummy data to create an icaltimetype
    struct icaltimetype dtstart_time;
    dtstart_time.year = 2023; // Using a fixed year for simplicity
    dtstart_time.zone = nullptr; // No timezone for this test

    // Set the DTSTART property
    icalcomponent_set_dtstart(component, dtstart_time);

    // Fuzz icalproperty_get_datetime_with_component
    struct icaltimetype datetime = icalproperty_get_datetime_with_component(property, component);

    // Check if the datetime is null
    if (icaltime_is_null_time(datetime)) {
        // Handle null time scenario
    }

    // Fuzz icalcomponent_get_dtstart
    struct icaltimetype start_time = icalcomponent_get_dtstart(component);

    // Fuzz icalcomponent_set_dtend
    struct icaltimetype dtend_time;
    dtend_time.year = 2023; // Using a fixed year for simplicity
    dtend_time.zone = nullptr; // No timezone for this test
    icalcomponent_set_dtend(component, dtend_time);

    // Fuzz icalcomponent_get_due
    struct icaltimetype due_time = icalcomponent_get_due(component);

    // Fuzz icalcomponent_get_duration
    struct icaldurationtype duration = icalcomponent_get_duration(component);

    // Cleanup
    icalproperty_free(property);
    icalcomponent_free(component);

    return 0;
}