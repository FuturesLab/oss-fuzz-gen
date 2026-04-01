// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_set_due at icalcomponent.c:2634:6 in icalcomponent.h
// icalcomponent_set_dtstart at icalcomponent.c:1533:6 in icalcomponent.h
// icalcomponent_get_due at icalcomponent.c:2613:21 in icalcomponent.h
// icalcomponent_set_sequence at icalcomponent.c:1955:6 in icalcomponent.h
// icalcomponent_set_duration at icalcomponent.c:1647:6 in icalcomponent.h
// icalcomponent_set_dtstamp at icalcomponent.c:1710:6 in icalcomponent.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "ical.h"
#include "ical.h"
#include <cstring>
#include <cstdint>
#include <cstdlib>

static icalcomponent* create_vtodo_component() {
    icalcomponent* comp = icalcomponent_new(ICAL_VTODO_COMPONENT);
    return comp;
}

static struct icaltimetype create_random_icaltime() {
    struct icaltimetype time;
    time.year = rand() % 3000; // Random year
    time.zone = icaltimezone_get_utc_timezone(); // Use UTC for simplicity
    return time;
}

static struct icaldurationtype create_random_icalduration() {
    struct icaldurationtype duration;
    duration.is_neg = rand() % 2;
    duration.days = rand() % 100;
    return duration;
}

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Not enough data to proceed

    icalcomponent* comp = create_vtodo_component();
    if (!comp) return 0; // Failed to create component

    struct icaltimetype due_time = create_random_icaltime();
    struct icaltimetype dtstart_time = create_random_icaltime();
    struct icaldurationtype duration = create_random_icalduration();

    int sequence = Data[0]; // Use first byte as sequence number

    // Fuzz the set_due function
    icalcomponent_set_due(comp, due_time);

    // Fuzz the set_dtstart function
    icalcomponent_set_dtstart(comp, dtstart_time);

    // Fuzz the get_due function
    icalcomponent_get_due(comp);

    // Fuzz the set_duration function
    icalcomponent_set_duration(comp, duration);

    // Fuzz the set_sequence function
    icalcomponent_set_sequence(comp, sequence);

    // Fuzz the set_dtstamp function
    icalcomponent_set_dtstamp(comp, dtstart_time);

    // Clean up
    icalcomponent_free(comp);

    return 0;
}