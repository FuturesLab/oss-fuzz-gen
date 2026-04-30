// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_foreach_tzid at icalcomponent.c:2393:6 in icalcomponent.h
// icalcomponent_new_vlocation at icalcomponent.c:2125:16 in icalcomponent.h
// icalcomponent_merge_component at icalcomponent.c:2139:6 in icalcomponent.h
// icalcomponent_new_vagenda at icalcomponent.c:2070:16 in icalcomponent.h
// icalcomponent_set_recurrenceid at icalcomponent.c:1839:6 in icalcomponent.h
// icalcomponent_add_component at icalcomponent.c:509:6 in icalcomponent.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    // Create a dummy VEVENT component
    icalcomponent *event = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (!event) return 0;

    // Create a dummy VAGENDA component
    icalcomponent *vagenda = icalcomponent_new_vagenda();
    if (!vagenda) {
        icalcomponent_free(event);
        return 0;
    }

    // Create a dummy VLOCATION component
    icalcomponent *vlocation = icalcomponent_new_vlocation();
    if (!vlocation) {
        icalcomponent_free(event);
        icalcomponent_free(vagenda);
        return 0;
    }

    // Add components to a parent VCALENDAR component
    icalcomponent *vcalendar = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    if (!vcalendar) {
        icalcomponent_free(event);
        icalcomponent_free(vagenda);
        icalcomponent_free(vlocation);
        return 0;
    }

    icalcomponent_add_component(vcalendar, event);
    icalcomponent_add_component(vcalendar, vagenda);
    icalcomponent_add_component(vcalendar, vlocation);

    // Create another VCALENDAR component to merge
    icalcomponent *vcalendar_to_merge = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    if (!vcalendar_to_merge) {
        icalcomponent_free(vcalendar);
        return 0;
    }

    // Merge two VCALENDAR components
    icalcomponent_merge_component(vcalendar, vcalendar_to_merge);

    // Define a simple callback function for foreach_tzid
    auto tzid_callback = [](icalparameter *param, void *data) {
        // Just a placeholder to demonstrate using the callback
    };

    // Use foreach_tzid on the vcalendar component
    icalcomponent_foreach_tzid(vcalendar, tzid_callback, nullptr);

    // Prepare a dummy icaltimetype
    icaltimetype recurrence_id;
    recurrence_id.year = 2023;
    recurrence_id.zone = nullptr;

    // Set the recurrence ID for the event
    icalcomponent_set_recurrenceid(event, recurrence_id);

    // Clean up
    icalcomponent_free(vcalendar);

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

        LLVMFuzzerTestOneInput_23(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    