// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_get_next_component at icalcomponent.c:627:16 in icalcomponent.h
// icalcomponent_get_first_component at icalcomponent.c:611:16 in icalcomponent.h
// icalcomponent_isa at icalcomponent.c:304:20 in icalcomponent.h
// icalcomponent_get_first_real_component at icalcomponent.c:647:16 in icalcomponent.h
// icalcomponent_get_inner at icalcomponent.c:1490:16 in icalcomponent.h
// icalcomponent_get_dtend at icalcomponent.c:1566:21 in icalcomponent.h
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
#include <libical/icalcomponent.h>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <libical/icaltime.h>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <libical/icaltimezone.h>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <libical/icalarray.h>

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(icalcomponent_kind)) return 0;

    // Create a dummy VCALENDAR component
    icalcomponent *root = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    if (!root) return 0;

    // Create a dummy VEVENT component
    icalcomponent *event = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (!event) {
        icalcomponent_free(root);
        return 0;
    }

    // Add the VEVENT to the VCALENDAR
    icalcomponent_add_component(root, event);

    // Read a kind from the input data
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(Data[0]);

    // Invoke icalcomponent_get_next_component
    icalcomponent *next_component = icalcomponent_get_next_component(root, kind);
    if (next_component) {
        icalcomponent_isa(next_component);
    }

    // Invoke icalcomponent_get_first_component
    icalcomponent *first_component = icalcomponent_get_first_component(root, kind);
    if (first_component) {
        icalcomponent_isa(first_component);
    }

    // Invoke icalcomponent_get_first_real_component
    const icalcomponent *first_real_component = icalcomponent_get_first_real_component(root);
    if (first_real_component) {
        icalcomponent_isa(first_real_component);
    }

    // Invoke icalcomponent_get_inner
    icalcomponent *inner_component = icalcomponent_get_inner(root);
    if (inner_component) {
        icalcomponent_isa(inner_component);
    }

    // Invoke icalcomponent_get_dtend
    struct icaltimetype dtend = icalcomponent_get_dtend(event);
    (void)dtend; // Use dtend to avoid unused variable warning

    // Clean up
    icalcomponent_free(root);

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

        LLVMFuzzerTestOneInput_7(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    