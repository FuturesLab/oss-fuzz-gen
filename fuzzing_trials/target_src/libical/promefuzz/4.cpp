// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_begin_component at icalcomponent.c:1342:14 in icalcomponent.h
// icalcomponent_end_component at icalcomponent.c:1365:14 in icalcomponent.h
// icalcompiter_next at icalcomponent.c:1387:16 in icalcomponent.h
// icalcompiter_deref at icalcomponent.c:1425:16 in icalcomponent.h
// icalcomponent_get_first_component at icalcomponent.c:611:16 in icalcomponent.h
// icalcomponent_get_current_component at icalcomponent.c:600:16 in icalcomponent.h
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

#include <cstdint>
#include <cstdlib>

static icalcomponent* create_dummy_component() {
    icalcomponent* component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    icalcomponent* vevent = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalcomponent_add_component(component, vevent);
    return component;
}

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Create a dummy component to work with
    icalcomponent* component = create_dummy_component();

    // Choose a component kind based on fuzzing data
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES);

    // Begin component iteration
    icalcompiter iter = icalcomponent_begin_component(component, kind);

    // Traverse components using the iterator
    while (icalcompiter_deref(&iter)) {
        icalcomponent* current_component = icalcompiter_deref(&iter);
        if (current_component) {
            // Use icalcomponent_get_current_component
            icalcomponent_get_current_component(current_component);
        }
        icalcompiter_next(&iter);
    }

    // End component iteration
    iter = icalcomponent_end_component(component, kind);

    // Use icalcomponent_get_first_component
    icalcomponent* first_component = icalcomponent_get_first_component(component, kind);
    if (first_component) {
        icalcomponent_get_current_component(first_component);
    }

    // Clean up
    icalcomponent_free(component);

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

        LLVMFuzzerTestOneInput_4(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    