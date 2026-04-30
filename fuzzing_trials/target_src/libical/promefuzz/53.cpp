// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_get_timezone at icalcomponent.c:2430:15 in icalcomponent.h
// icalcomponent_new_xdaylight at icalcomponent.c:2065:16 in icalcomponent.h
// icalcomponent_new_vtimezone at icalcomponent.c:2055:16 in icalcomponent.h
// icalcomponent_add_component at icalcomponent.c:509:6 in icalcomponent.h
// icalcomponent_add_property at icalcomponent.c:385:6 in icalcomponent.h
// icalcomponent_new_xpatch at icalcomponent.c:2115:16 in icalcomponent.h
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
#include <cstring>
#include <iostream>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_53(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a new XPATCH component
    icalcomponent *xpatch_component = icalcomponent_new_xpatch();
    if (!xpatch_component) return 0;

    // Create a new XDAYLIGHT component
    icalcomponent *xdaylight_component = icalcomponent_new_xdaylight();
    if (!xdaylight_component) {
        icalcomponent_free(xpatch_component);
        return 0;
    }

    // Create a new VTIMEZONE component
    icalcomponent *vtimezone_component = icalcomponent_new_vtimezone();
    if (!vtimezone_component) {
        icalcomponent_free(xpatch_component);
        icalcomponent_free(xdaylight_component);
        return 0;
    }

    // Add the XDAYLIGHT component to the XPATCH component
    icalcomponent_add_component(xpatch_component, xdaylight_component);

    // Add the VTIMEZONE component to the XPATCH component
    icalcomponent_add_component(xpatch_component, vtimezone_component);

    // Create a property and add it to the XPATCH component
    icalproperty *property = icalproperty_new(ICAL_TZID_PROPERTY);
    if (property) {
        icalcomponent_add_property(xpatch_component, property);
    }

    // Use the data to get a timezone from the XPATCH component
    char tzid[256];
    size_t tzid_length = Size < 255 ? Size : 255;
    memcpy(tzid, Data, tzid_length);
    tzid[tzid_length] = '\0';

    icaltimezone *timezone = icalcomponent_get_timezone(xpatch_component, tzid);

    // Clean up
    if (timezone) {
        // Assume some usage of timezone
    }
    icalcomponent_free(xpatch_component);

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

        LLVMFuzzerTestOneInput_53(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    