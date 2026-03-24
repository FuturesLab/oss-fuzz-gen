// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalproperty_recurrence_is_excluded at icalcomponent.c:738:6 in icalcomponent.h
// icalcomponent_get_recurrenceid at icalcomponent.c:1859:21 in icalcomponent.h
// icalcomponent_get_dtstart at icalcomponent.c:1553:21 in icalcomponent.h
// icalcomponent_set_recurrenceid at icalcomponent.c:1839:6 in icalcomponent.h
// icalcomponent_foreach_recurrence at icalcomponent.c:927:6 in icalcomponent.h
// icalcomponent_set_dtend at icalcomponent.c:1622:6 in icalcomponent.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <fstream>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <cstring>

void dummy_callback(icalcomponent *comp, const struct icaltime_span *span, void *data) {
    // ...
}

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(icalcomponent_kind) + 2 * sizeof(icaltimetype)) {
        return 0; // Not enough data to proceed
    }

    icalcomponent_kind kind = static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES);
    icalcomponent *comp = icalcomponent_new(kind);

    struct icaltimetype start, end;
    std::memcpy(&start, Data + 1, sizeof(icaltimetype));
    std::memcpy(&end, Data + 1 + sizeof(icaltimetype), sizeof(icaltimetype));

    // Initialize timezones to avoid null pointer dereference
    const icaltimezone *utc_zone = icaltimezone_get_utc_timezone();
    start.zone = utc_zone;
    end.zone = utc_zone;

    // Test icalcomponent_get_dtstart
    struct icaltimetype dtstart = icalcomponent_get_dtstart(comp);

    // Test icalcomponent_foreach_recurrence
    icalcomponent_foreach_recurrence(comp, start, end, dummy_callback, nullptr);

    // Test icalcomponent_set_dtend
    icalcomponent_set_dtend(comp, end);

    // Test icalcomponent_set_recurrenceid
    icalcomponent_set_recurrenceid(comp, start);

    // Test icalproperty_recurrence_is_excluded
    bool is_excluded = icalproperty_recurrence_is_excluded(comp, &start, &end);

    // Test icalcomponent_get_recurrenceid
    struct icaltimetype recurrence_id = icalcomponent_get_recurrenceid(comp);

    // Cleanup
    icalcomponent_free(comp);

    return 0;
}