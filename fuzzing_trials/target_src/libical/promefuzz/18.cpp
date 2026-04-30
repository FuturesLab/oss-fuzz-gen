// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_get_relcalid at icalcomponent.c:2591:13 in icalcomponent.h
// icalcomponent_get_uid at icalcomponent.c:1816:13 in icalcomponent.h
// icalcomponent_set_uid at icalcomponent.c:1804:6 in icalcomponent.h
// icalcomponent_get_description at icalcomponent.c:1897:13 in icalcomponent.h
// icalcomponent_get_x_name at icalcomponent.c:337:13 in icalcomponent.h
// icalcomponent_get_summary at icalcomponent.c:1746:13 in icalcomponent.h
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
#include <libical/icalcomponent.h>

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy icalcomponent
    icalcomponent *comp = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (!comp) return 0;

    // Use a portion of the input data as a potential UID
    std::string uid(reinterpret_cast<const char *>(Data), Size);
    icalcomponent_set_uid(comp, uid.c_str());

    // Fetch and print the UID
    const char *retrieved_uid = icalcomponent_get_uid(comp);
    if (retrieved_uid) {
        std::cout << "UID: " << retrieved_uid << std::endl;
    }

    // Fetch and print the X name
    const char *x_name = icalcomponent_get_x_name(comp);
    if (x_name) {
        std::cout << "X Name: " << x_name << std::endl;
    }

    // Fetch and print the RELCALID
    const char *relcalid = icalcomponent_get_relcalid(comp);
    if (relcalid) {
        std::cout << "RELCALID: " << relcalid << std::endl;
    }

    // Fetch and print the description
    const char *description = icalcomponent_get_description(comp);
    if (description) {
        std::cout << "Description: " << description << std::endl;
    }

    // Fetch and print the summary
    const char *summary = icalcomponent_get_summary(comp);
    if (summary) {
        std::cout << "Summary: " << summary << std::endl;
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

        LLVMFuzzerTestOneInput_18(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    