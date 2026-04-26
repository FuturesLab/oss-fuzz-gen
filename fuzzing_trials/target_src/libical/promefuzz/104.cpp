// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_foreach_recurrence at icalcomponent.c:927:6 in icalcomponent.h
// icalcomponent_get_recurrenceid at icalcomponent.c:1859:21 in icalcomponent.h
// icalcomponent_get_dtstart at icalcomponent.c:1553:21 in icalcomponent.h
// icalcomponent_set_recurrenceid at icalcomponent.c:1839:6 in icalcomponent.h
// icalproperty_recurrence_is_excluded at icalcomponent.c:738:6 in icalcomponent.h
// icalcomponent_add_component at icalcomponent.c:509:6 in icalcomponent.h
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
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_104(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy VEVENT component
    icalcomponent *vevent = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Create dummy start and end times
    struct icaltimetype start_time = icaltime_from_timet_with_zone(time(NULL), 0, NULL);
    struct icaltimetype end_time = icaltime_from_timet_with_zone(time(NULL) + 3600, 0, NULL);

    // Callback function for icalcomponent_foreach_recurrence
    auto callback = [](const icalcomponent *comp, const struct icaltime_span *span, void *data) {
        // Dummy callback implementation
    };

    // Fuzz icalcomponent_foreach_recurrence
    icalcomponent_foreach_recurrence(vevent, start_time, end_time, callback, nullptr);

    // Fuzz icalcomponent_get_dtstart
    struct icaltimetype dtstart = icalcomponent_get_dtstart(vevent);

    // Fuzz icalproperty_recurrence_is_excluded
    bool is_excluded = icalproperty_recurrence_is_excluded(vevent, &start_time, &end_time);

    // Create a dummy child component
    icalcomponent *child = icalcomponent_new(ICAL_VTIMEZONE_COMPONENT);

    // Fuzz icalcomponent_add_component
    icalcomponent_add_component(vevent, child);

    // Fuzz icalcomponent_get_recurrenceid
    struct icaltimetype recurrence_id = icalcomponent_get_recurrenceid(vevent);

    // Fuzz icalcomponent_set_recurrenceid
    icalcomponent_set_recurrenceid(vevent, dtstart);

    // Cleanup
    icalcomponent_free(vevent);

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

        LLVMFuzzerTestOneInput_104(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    