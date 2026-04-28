// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_new_vfreebusy at icalcomponent.c:2050:16 in icalcomponent.h
// icalcomponent_new_xdaylight at icalcomponent.c:2065:16 in icalcomponent.h
// icalcomponent_new_vpatch at icalcomponent.c:2110:16 in icalcomponent.h
// icalcomponent_new_xstandard at icalcomponent.c:2060:16 in icalcomponent.h
// icalcomponent_new_vtimezone at icalcomponent.c:2055:16 in icalcomponent.h
// icalcomponent_new_vcalendar at icalcomponent.c:2025:16 in icalcomponent.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <stdint.h>
#include <stddef.h>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <icalcomponent.h>

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    // Create various calendar components
    icalcomponent *xstandard = icalcomponent_new_xstandard();
    icalcomponent *vcalendar = icalcomponent_new_vcalendar();
    icalcomponent *vtimezone = icalcomponent_new_vtimezone();
    icalcomponent *vfreebusy = icalcomponent_new_vfreebusy();
    icalcomponent *vpatch = icalcomponent_new_vpatch();
    icalcomponent *xdaylight = icalcomponent_new_xdaylight();

    // Perform cleanup by freeing the created components
    if (xstandard) {
        icalcomponent_free(xstandard);
    }
    if (vcalendar) {
        icalcomponent_free(vcalendar);
    }
    if (vtimezone) {
        icalcomponent_free(vtimezone);
    }
    if (vfreebusy) {
        icalcomponent_free(vfreebusy);
    }
    if (vpatch) {
        icalcomponent_free(vpatch);
    }
    if (xdaylight) {
        icalcomponent_free(xdaylight);
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

        LLVMFuzzerTestOneInput_10(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    