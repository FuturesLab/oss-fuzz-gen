// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_set_sequence at icalcomponent.c:1955:6 in icalcomponent.h
// icalcomponent_get_sequence at icalcomponent.c:1967:5 in icalcomponent.h
// icalcomponent_get_inner at icalcomponent.c:1490:16 in icalcomponent.h
// icalcomponent_get_next_component at icalcomponent.c:627:16 in icalcomponent.h
// icalcomponent_set_dtstart at icalcomponent.c:1533:6 in icalcomponent.h
// icalcomponent_new_valarm at icalcomponent.c:2045:16 in icalcomponent.h
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
#include <stdint.h>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <libical/icalcomponent.h>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <libical/icaltime.h>

static icalcomponent* create_component_from_data(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return nullptr;
    }
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES);
    return icalcomponent_new(kind);
}

extern "C" int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    icalcomponent *comp = create_component_from_data(Data, Size);
    if (!comp) {
        return 0;
    }

    // Test icalcomponent_get_inner
    icalcomponent *inner = icalcomponent_get_inner(comp);
    if (inner) {
        // Do something with inner, like checking its kind
        icalcomponent_kind inner_kind = icalcomponent_isa(inner);
        (void)inner_kind; // Suppress unused variable warning
    }

    // Test icalcomponent_set_dtstart
    struct icaltimetype dtstart = icaltime_from_timet_with_zone(time(NULL), 0, nullptr);
    icalcomponent_set_dtstart(comp, dtstart);

    // Test icalcomponent_get_sequence
    int sequence = icalcomponent_get_sequence(comp);
    (void)sequence; // Suppress unused variable warning

    // Test icalcomponent_get_next_component
    icalcomponent *next = icalcomponent_get_next_component(comp, ICAL_VEVENT_COMPONENT);
    if (next) {
        // Do something with next, like checking its kind
        icalcomponent_kind next_kind = icalcomponent_isa(next);
        (void)next_kind; // Suppress unused variable warning
    }

    // Test icalcomponent_new_valarm
    icalcomponent *alarm = icalcomponent_new_valarm();
    if (alarm) {
        icalcomponent_add_component(comp, alarm);
    }

    // Test icalcomponent_set_sequence
    icalcomponent_set_sequence(comp, static_cast<int>(Data[0]));

    // Cleanup
    icalcomponent_free(comp);

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

        LLVMFuzzerTestOneInput_43(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    