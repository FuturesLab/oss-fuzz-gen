// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_get_span at icalcomponent.c:670:15 in icalcomponent.h
// icalcomponent_merge_component at icalcomponent.c:2139:6 in icalcomponent.h
// icalcomponent_add_component at icalcomponent.c:509:6 in icalcomponent.h
// icalcomponent_set_recurrenceid at icalcomponent.c:1839:6 in icalcomponent.h
// icalcomponent_normalize at icalcomponent.c:2832:6 in icalcomponent.h
// icalcomponent_new_vevent at icalcomponent.c:2030:16 in icalcomponent.h
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

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create two VCALENDAR components
    icalcomponent *vcalendar1 = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    icalcomponent *vcalendar2 = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    
    // Create a VEVENT component and add it to the first VCALENDAR
    icalcomponent *vevent = icalcomponent_new_vevent();
    icalcomponent_add_component(vcalendar1, vevent);

    // Normalize the first VCALENDAR component
    icalcomponent_normalize(vcalendar1);

    // Merge the second VCALENDAR into the first
    icalcomponent_merge_component(vcalendar1, vcalendar2);

    // Get the time span of the first VCALENDAR
    icaltime_span span = icalcomponent_get_span(vcalendar1);

    // Set a recurrence ID on the VEVENT
    icaltimetype recurrence_id;
    recurrence_id.year = 2023;
    recurrence_id.zone = nullptr;
    icalcomponent_set_recurrenceid(vevent, recurrence_id);

    // Clean up components
    icalcomponent_free(vcalendar1);

    // Write Data to a dummy file if needed
    std::ofstream dummyFile("./dummy_file", std::ios::binary);
    if (dummyFile.is_open()) {
        dummyFile.write(reinterpret_cast<const char*>(Data), Size);
        dummyFile.close();
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

        LLVMFuzzerTestOneInput_20(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    