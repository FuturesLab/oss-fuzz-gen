#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "libical/ical.h"
#include "libical/ical.h"
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

extern "C" int LLVMFuzzerTestOneInput_59(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    } // Not enough data to proceed

    icalcomponent* comp = create_vtodo_component();
    if (!comp) {
        return 0;
    } // Failed to create component

    struct icaltimetype due_time = create_random_icaltime();
    struct icaltimetype dtstart_time = create_random_icaltime();
    struct icaldurationtype duration = create_random_icalduration();

    int sequence = Data[0]; // Use first byte as sequence number

    // Fuzz the set_due function

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalcomponent_set_due with icalcomponent_set_dtend
    icalcomponent_set_dtend(comp, due_time);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Fuzz the set_dtstart function

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalcomponent_set_dtstart with icalcomponent_set_due
    icalcomponent_set_due(comp, dtstart_time);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



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