// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_end_component at icalcomponent.c:1365:14 in icalcomponent.h
// icalcomponent_begin_component at icalcomponent.c:1342:14 in icalcomponent.h
// icalcompiter_next at icalcomponent.c:1387:16 in icalcomponent.h
// icalcompiter_deref at icalcomponent.c:1425:16 in icalcomponent.h
// icalcomponent_remove_component at icalcomponent.c:543:6 in icalcomponent.h
// icalcomponent_get_inner at icalcomponent.c:1490:16 in icalcomponent.h
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
#include <icalcomponent.h>

extern "C" int LLVMFuzzerTestOneInput_117(const uint8_t *Data, size_t Size) {
    // Prepare a dummy file
    std::ofstream dummyFile("./dummy_file");
    if (!dummyFile.is_open()) {
        return 0;
    }
    dummyFile.write(reinterpret_cast<const char*>(Data), Size);
    dummyFile.close();

    // Initialize components and iterators
    icalcomponent *parent = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    icalcomponent *child = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalcomponent_add_component(parent, child);

    icalcompiter iter = icalcomponent_begin_component(parent, ICAL_VEVENT_COMPONENT);
    icalcomponent *currentComp = icalcompiter_deref(&iter);

    // Fuzz icalcompiter_next
    icalcomponent *nextComp = icalcompiter_next(&iter);

    // Fuzz icalcomponent_remove_component
    icalcomponent_remove_component(parent, child);

    // Fuzz icalcomponent_get_inner
    icalcomponent *innerComp = icalcomponent_get_inner(parent);

    // Fuzz icalcomponent_end_component
    icalcompiter endIter = icalcomponent_end_component(parent, ICAL_VEVENT_COMPONENT);

    // Cleanup
    icalcomponent_free(parent);
    // Note: child is already removed and should not be freed again

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

        LLVMFuzzerTestOneInput_117(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    