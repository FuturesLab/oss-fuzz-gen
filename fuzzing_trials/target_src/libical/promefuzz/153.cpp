// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icaltimezone_truncate_vtimezone at icaltimezone.c:2327:6 in icaltimezone.h
// icalcomponent_set_dtstart at icalcomponent.c:1533:6 in icalcomponent.h
// icalcomponent_set_dtend at icalcomponent.c:1622:6 in icalcomponent.h
// icalcomponent_get_dtstart at icalcomponent.c:1553:21 in icalcomponent.h
// icalcomponent_set_due at icalcomponent.c:2634:6 in icalcomponent.h
// icalproperty_get_datetime_with_component at icalproperty.c:1050:21 in icalcomponent.h
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
#include <cassert>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <libical/ical.h>

static icalcomponent* create_dummy_component(icalcomponent_kind kind) {
    icalcomponent* comp = icalcomponent_new(kind);
    assert(comp != nullptr);
    return comp;
}

static icaltimetype create_dummy_icaltime() {
    icaltimetype tt;
    tt.year = 2023;
    tt.zone = icaltimezone_get_utc_timezone();
    return tt;
}

extern "C" int LLVMFuzzerTestOneInput_153(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Not enough data to proceed

    // Create dummy components for testing
    icalcomponent* vevent = create_dummy_component(ICAL_VEVENT_COMPONENT);
    icalcomponent* vtodo = create_dummy_component(ICAL_VTODO_COMPONENT);
    icalcomponent* vtimezone = create_dummy_component(ICAL_VTIMEZONE_COMPONENT);

    // Create a dummy icaltime
    icaltimetype dummy_time = create_dummy_icaltime();

    // Test icalcomponent_set_dtend
    icalcomponent_set_dtend(vevent, dummy_time);

    // Test icalcomponent_set_dtstart
    icalcomponent_set_dtstart(vevent, dummy_time);

    // Test icalcomponent_get_dtstart
    icaltimetype dtstart = icalcomponent_get_dtstart(vevent);
    (void)dtstart; // Avoid unused variable warning

    // Test icalproperty_get_datetime_with_component
    icalproperty* prop = icalproperty_new_dtstart(dummy_time);
    icaltimetype datetime = icalproperty_get_datetime_with_component(prop, vevent);
    (void)datetime; // Avoid unused variable warning
    icalproperty_free(prop);

    // Test icaltimezone_truncate_vtimezone
    icaltimezone_truncate_vtimezone(vtimezone, dummy_time, dummy_time, false);

    // Test icalcomponent_set_due
    icalcomponent_set_due(vtodo, dummy_time);

    // Cleanup
    icalcomponent_free(vevent);
    icalcomponent_free(vtodo);
    icalcomponent_free(vtimezone);

    return 0;
}
    #ifdef INC_MAIN
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdint.h>
    int main(int argc, char *argv[])
    {
        FILE *f;
        uint8_t *data = NULL;
        long size;

        if(argc < 2)
            exit(0);

        f = fopen(argv[1], "rb");
        if(f == NULL)
            exit(0);

        fseek(f, 0, SEEK_END);

        size = ftell(f);
        rewind(f);

        if(size < 1 + 1)
            exit(0);

        data = (uint8_t *)malloc((size_t)size);
        if(data == NULL)
            exit(0);

        if(fread(data, (size_t)size, 1, f) != 1)
            exit(0);

        LLVMFuzzerTestOneInput_153(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    