// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_get_span at icalcomponent.c:670:15 in icalcomponent.h
// icalcomponent_new_xavailable at icalcomponent.c:2090:16 in icalcomponent.h
// icalcomponent_new_vavailability at icalcomponent.c:2085:16 in icalcomponent.h
// icalcomponent_new_vtodo at icalcomponent.c:2035:16 in icalcomponent.h
// icalcomponent_new_vtimezone at icalcomponent.c:2055:16 in icalcomponent.h
// icalcomponent_new_vevent at icalcomponent.c:2030:16 in icalcomponent.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <icalcomponent.h>

extern "C" int LLVMFuzzerTestOneInput_135(const uint8_t *Data, size_t Size) {
    // Step 1: Prepare the environment and create components
    icalcomponent *vtimezone = icalcomponent_new_vtimezone();
    icalcomponent *vavailability = icalcomponent_new_vavailability();
    icalcomponent *vevent = icalcomponent_new_vevent();
    icalcomponent *vtodo = icalcomponent_new_vtodo();
    icalcomponent *xavailable = icalcomponent_new_xavailable();

    // Step 2: Perform operations on the components
    if (vtimezone) {
        icaltime_span span = icalcomponent_get_span(vtimezone);
    }
    if (vavailability) {
        icaltime_span span = icalcomponent_get_span(vavailability);
    }
    if (vevent) {
        icaltime_span span = icalcomponent_get_span(vevent);
    }
    if (vtodo) {
        icaltime_span span = icalcomponent_get_span(vtodo);
    }
    if (xavailable) {
        icaltime_span span = icalcomponent_get_span(xavailable);
    }

    // Step 3: Cleanup
    if (vtimezone) {
        icalcomponent_free(vtimezone);
    }
    if (vavailability) {
        icalcomponent_free(vavailability);
    }
    if (vevent) {
        icalcomponent_free(vevent);
    }
    if (vtodo) {
        icalcomponent_free(vtodo);
    }
    if (xavailable) {
        icalcomponent_free(xavailable);
    }

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

        LLVMFuzzerTestOneInput_135(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    