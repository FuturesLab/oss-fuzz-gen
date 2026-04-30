// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_get_dtstamp at icalcomponent.c:1722:21 in icalcomponent.h
// icalcomponent_set_dtstamp at icalcomponent.c:1710:6 in icalcomponent.h
// icalcomponent_get_dtstart at icalcomponent.c:1553:21 in icalcomponent.h
// icalcomponent_set_dtstart at icalcomponent.c:1533:6 in icalcomponent.h
// icalcomponent_set_dtend at icalcomponent.c:1622:6 in icalcomponent.h
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
#include <cstring>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <libical/icalcomponent.h>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <libical/icaltime.h>

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) + sizeof(icaltimetype)) {
        return 0; // Not enough data to proceed
    }

    // Create a dummy icalcomponent
    icalcomponent *comp = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (!comp) {
        return 0; // Failed to create component
    }

    // Extract an integer to decide which function to test
    int choice = *reinterpret_cast<const int*>(Data);
    Data += sizeof(int);
    Size -= sizeof(int);

    // Create an icaltimetype from the remaining data
    icaltimetype time = icaltime_null_time();
    if (Size >= sizeof(icaltimetype)) {
        std::memcpy(&time, Data, sizeof(icaltimetype));
        // Ensure the timezone pointer is valid or null
        time.zone = nullptr; // Set to null as a safe default
    }

    switch (choice % 6) {
        case 0: {
            // Test icalcomponent_get_dtstamp
            icaltimetype dtstamp = icalcomponent_get_dtstamp(comp);
            (void)dtstamp; // Suppress unused variable warning
            break;
        }
        case 1: {
            // Test icalcomponent_set_dtstart
            icalcomponent_set_dtstart(comp, time);
            break;
        }
        case 2: {
            // Test icalcomponent_set_dtstamp
            icalcomponent_set_dtstamp(comp, time);
            break;
        }
        case 3: {
            // Test icalcomponent_set_dtend
            icalcomponent_set_dtend(comp, time);
            break;
        }
        case 4: {
            // Test icalcomponent_new_valarm
            icalcomponent *valarm = icalcomponent_new_valarm();
            if (valarm) {
                icalcomponent_free(valarm);
            }
            break;
        }
        case 5: {
            // Test icalcomponent_get_dtstart
            icaltimetype dtstart = icalcomponent_get_dtstart(comp);
            (void)dtstart; // Suppress unused variable warning
            break;
        }
        default:
            break;
    }

    // Clean up
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

        LLVMFuzzerTestOneInput_14(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    