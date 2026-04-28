// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_get_uid at icalcomponent.c:1816:13 in icalcomponent.h
// icalcomponent_get_location at icalcomponent.c:1932:13 in icalcomponent.h
// icalcomponent_set_description at icalcomponent.c:1885:6 in icalcomponent.h
// icalcomponent_get_comment at icalcomponent.c:1781:13 in icalcomponent.h
// icalcomponent_get_summary at icalcomponent.c:1746:13 in icalcomponent.h
// icalcomponent_as_ical_string at icalcomponent.c:215:7 in icalcomponent.h
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
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Create a dummy icalcomponent for testing purposes
    icalcomponent *comp = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (!comp) {
        return 0;
    }

    // Use the data to set a description
    std::string description(reinterpret_cast<const char*>(Data), Size);
    icalcomponent_set_description(comp, description.c_str());

    // Retrieve and print various properties
    const char *comment = icalcomponent_get_comment(comp);
    if (comment) {
        std::cout << "Comment: " << comment << std::endl;
    }

    const char *location = icalcomponent_get_location(comp);
    if (location) {
        std::cout << "Location: " << location << std::endl;
    }

    const char *summary = icalcomponent_get_summary(comp);
    if (summary) {
        std::cout << "Summary: " << summary << std::endl;
    }

    const char *uid = icalcomponent_get_uid(comp);
    if (uid) {
        std::cout << "UID: " << uid << std::endl;
    }

    char *ical_str = icalcomponent_as_ical_string(comp);
    if (ical_str) {
        std::cout << "iCalendar String: " << ical_str << std::endl;
        // Do not free ical_str as it is managed by libical's internal memory management
    }

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

        LLVMFuzzerTestOneInput_9(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    