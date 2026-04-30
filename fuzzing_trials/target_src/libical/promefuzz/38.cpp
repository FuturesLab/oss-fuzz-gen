// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_set_duration at icalcomponent.c:1647:6 in icalcomponent.h
// icalcomponent_get_duration at icalcomponent.c:1664:25 in icalcomponent.h
// icalcomponent_clone at icalcomponent.c:129:16 in icalcomponent.h
// icalcomponent_new_vevent at icalcomponent.c:2030:16 in icalcomponent.h
// icalcomponent_set_dtend at icalcomponent.c:1622:6 in icalcomponent.h
// icalcomponent_get_sequence at icalcomponent.c:1967:5 in icalcomponent.h
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
#include <fstream>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size) {
    // Prepare environment for testing
    icalcomponent *vevent = icalcomponent_new_vevent();
    if (!vevent) return 0; // If creation fails, exit

    // Test icalcomponent_clone
    icalcomponent *cloned_vevent = icalcomponent_clone(vevent);
    if (cloned_vevent) {
        // Test icalcomponent_get_sequence
        int sequence = icalcomponent_get_sequence(cloned_vevent);

        // Prepare a dummy icaltimetype for testing
        struct icaltimetype dtend_time;
        dtend_time.year = 2023;
        dtend_time.zone = nullptr;

        // Test icalcomponent_set_dtend
        icalcomponent_set_dtend(cloned_vevent, dtend_time);

        // Test icalcomponent_get_duration
        struct icaldurationtype duration = icalcomponent_get_duration(cloned_vevent);

        // Prepare a dummy icaldurationtype for testing
        struct icaldurationtype test_duration;
        test_duration.is_neg = 0;
        test_duration.days = 1;

        // Test icalcomponent_set_duration
        icalcomponent_set_duration(cloned_vevent, test_duration);

        // Clean up cloned component
        icalcomponent_free(cloned_vevent);
    }

    // Clean up original component
    icalcomponent_free(vevent);

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

        LLVMFuzzerTestOneInput_38(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    