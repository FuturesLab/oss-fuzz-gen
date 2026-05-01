// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_get_parent at icalcomponent.c:1226:16 in icalcomponent.h
// icalcomponent_set_parent at icalcomponent.c:1231:6 in icalcomponent.h
// icalcomponent_remove_component at icalcomponent.c:543:6 in icalcomponent.h
// icalcomponent_add_component at icalcomponent.c:509:6 in icalcomponent.h
// icalcomponent_new_vtimezone at icalcomponent.c:2055:16 in icalcomponent.h
// icalcomponent_isa at icalcomponent.c:304:20 in icalcomponent.h
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
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"

static icalcomponent* createRandomComponent() {
    icalcomponent_kind kinds[] = {
        ICAL_VEVENT_COMPONENT,
        ICAL_VTODO_COMPONENT,
        ICAL_VJOURNAL_COMPONENT,
        ICAL_VCALENDAR_COMPONENT,
        ICAL_VAGENDA_COMPONENT,
        ICAL_VFREEBUSY_COMPONENT,
        ICAL_VALARM_COMPONENT,
        ICAL_VTIMEZONE_COMPONENT,
        ICAL_VAVAILABILITY_COMPONENT,
        ICAL_VPOLL_COMPONENT,
        ICAL_VLOCATION_COMPONENT,
        ICAL_VRESOURCE_COMPONENT
    };
    int randomIndex = rand() % (sizeof(kinds) / sizeof(kinds[0]));
    icalcomponent *comp = icalcomponent_new(kinds[randomIndex]);
    return comp;
}

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    icalcomponent *parent = createRandomComponent();
    icalcomponent *child = createRandomComponent();

    // Test icalcomponent_add_component
    icalcomponent_add_component(parent, child);

    // Test icalcomponent_get_parent
    icalcomponent *retrievedParent = icalcomponent_get_parent(child);

    // Test icalcomponent_isa
    icalcomponent_kind kind = icalcomponent_isa(child);

    // Test icalcomponent_remove_component
    icalcomponent_remove_component(parent, child);

    // Test icalcomponent_set_parent
    icalcomponent_set_parent(child, parent);

    // Test icalcomponent_new_vtimezone
    icalcomponent *vtimezone = icalcomponent_new_vtimezone();

    // Clean up
    if (parent) {
        icalcomponent_free(parent);
    }
    if (child) {
        icalcomponent_free(child);
    }
    if (vtimezone) {
        icalcomponent_free(vtimezone);
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

        LLVMFuzzerTestOneInput_24(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    