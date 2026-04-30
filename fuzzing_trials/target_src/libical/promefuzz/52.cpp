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
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create components using the available API functions
    icalcomponent *xpatchComponent = icalcomponent_new_xpatch();
    icalcomponent *xdaylightComponent = icalcomponent_new_xdaylight();
    icalcomponent *vtimezoneComponent = icalcomponent_new_vtimezone();

    // Create a property and add it to a component
    icalproperty *property = icalproperty_new(ICAL_TZID_PROPERTY);
    icalcomponent_add_property(xpatchComponent, property);

    // Add components to a parent component
    icalcomponent_add_component(xpatchComponent, xdaylightComponent);
    icalcomponent_add_component(xpatchComponent, vtimezoneComponent);

    // Use the input data to create a tzid string and get timezone
    std::string tzid(reinterpret_cast<const char*>(Data), Size);
    icaltimezone *timezone = icalcomponent_get_timezone(xpatchComponent, tzid.c_str());

    // Clean up the created components
    icalcomponent_free(xpatchComponent);  // This will also free the child components
    // Property and timezone are managed by the component, no need to free separately

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

        LLVMFuzzerTestOneInput_52(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    