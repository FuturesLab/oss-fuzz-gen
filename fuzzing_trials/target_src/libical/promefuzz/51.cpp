// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_set_due at icalcomponent.c:2634:6 in icalcomponent.h
// icalcomponent_set_dtstamp at icalcomponent.c:1710:6 in icalcomponent.h
// icalcomponent_set_dtend at icalcomponent.c:1622:6 in icalcomponent.h
// icalcomponent_set_dtstart at icalcomponent.c:1533:6 in icalcomponent.h
// icalcomponent_new_vtimezone at icalcomponent.c:2055:16 in icalcomponent.h
// icalcomponent_get_dtstart at icalcomponent.c:1553:21 in icalcomponent.h
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
#include <cstdint>
#include <cstring>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <libical/icalcomponent.h>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <libical/icaltime.h>

static icaltimetype generate_icaltimetype(const uint8_t *Data, size_t Size) {
    icaltimetype time = icaltime_null_time();
    if (Size >= sizeof(int)) {
        int year;
        std::memcpy(&year, Data, sizeof(int));
        time.year = year;
    }
    return time;
}

extern "C" int LLVMFuzzerTestOneInput_51(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Create a new VTODO component
    icalcomponent *vtodo = icalcomponent_new(ICAL_VTODO_COMPONENT);
    if (!vtodo) return 0;

    // Create icaltimetype from input data
    icaltimetype due_time = generate_icaltimetype(Data, Size);

    // Fuzz icalcomponent_set_due
    icalcomponent_set_due(vtodo, due_time);

    // Fuzz icalcomponent_set_dtstart
    icalcomponent_set_dtstart(vtodo, due_time);

    // Fuzz icalcomponent_set_dtstamp
    icalcomponent_set_dtstamp(vtodo, due_time);

    // Fuzz icalcomponent_set_dtend
    icalcomponent_set_dtend(vtodo, due_time);

    // Fuzz icalcomponent_new_vtimezone
    icalcomponent *vtimezone = icalcomponent_new_vtimezone();
    if (vtimezone) {
        icalcomponent_free(vtimezone);
    }

    // Fuzz icalcomponent_get_dtstart
    icaltimetype dtstart_time = icalcomponent_get_dtstart(vtodo);

    // Clean up
    icalcomponent_free(vtodo);

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

        LLVMFuzzerTestOneInput_51(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    