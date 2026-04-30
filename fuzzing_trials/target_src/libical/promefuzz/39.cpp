// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_new_vjournal at icalcomponent.c:2040:16 in icalcomponent.h
// icalcomponent_new_vpoll at icalcomponent.c:2095:16 in icalcomponent.h
// icalcomponent_new_xvote at icalcomponent.c:2105:16 in icalcomponent.h
// icalcomponent_new_vquery at icalcomponent.c:2075:16 in icalcomponent.h
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
extern "C" {
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"
}

extern "C" int LLVMFuzzerTestOneInput_39(const uint8_t *Data, size_t Size) {
    // Create various iCalendar components
    icalcomponent *vpoll = icalcomponent_new_vpoll();
    icalcomponent *vtimezone = icalcomponent_new_vtimezone();
    icalcomponent *vjournal = icalcomponent_new_vjournal();
    icalcomponent *vevent = icalcomponent_new_vevent();
    icalcomponent *xvote = icalcomponent_new_xvote();
    icalcomponent *vquery = icalcomponent_new_vquery();

    // Perform some simple checks and cleanup
    if (vpoll) {
        // Do something with vpoll
        icalcomponent_free(vpoll);
    }
    if (vtimezone) {
        // Do something with vtimezone
        icalcomponent_free(vtimezone);
    }
    if (vjournal) {
        // Do something with vjournal
        icalcomponent_free(vjournal);
    }
    if (vevent) {
        // Do something with vevent
        icalcomponent_free(vevent);
    }
    if (xvote) {
        // Do something with xvote
        icalcomponent_free(xvote);
    }
    if (vquery) {
        // Do something with vquery
        icalcomponent_free(vquery);
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

        LLVMFuzzerTestOneInput_39(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    