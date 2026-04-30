// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_get_location at icalcomponent.c:1932:13 in icalcomponent.h
// icalcomponent_new_from_string at icalcomponent.c:124:16 in icalcomponent.h
// icalcomponent_get_comment at icalcomponent.c:1781:13 in icalcomponent.h
// icalcomponent_get_first_component at icalcomponent.c:611:16 in icalcomponent.h
// icalcomponent_get_recurrenceid at icalcomponent.c:1859:21 in icalcomponent.h
// icalcomponent_isa at icalcomponent.c:304:20 in icalcomponent.h
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
#include <cstdlib>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <libical/icalcomponent.h>

extern "C" int LLVMFuzzerTestOneInput_39(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Create a string from the input data
    std::string icalStr(reinterpret_cast<const char*>(Data), Size);

    // Use the icalcomponent_new_from_string function
    icalcomponent *component = icalcomponent_new_from_string(icalStr.c_str());

    if (component) {
        // Use the icalcomponent_get_location function
        const char *location = icalcomponent_get_location(component);

        // Use the icalcomponent_isa function
        icalcomponent_kind kind = icalcomponent_isa(component);

        // Use the icalcomponent_get_recurrenceid function
        struct icaltimetype recurrenceId = icalcomponent_get_recurrenceid(component);

        // Loop through different component kinds for icalcomponent_get_first_component
        for (int kindIndex = ICAL_NO_COMPONENT; kindIndex < ICAL_NUM_COMPONENT_TYPES; ++kindIndex) {
            icalcomponent *firstComponent = icalcomponent_get_first_component(component, static_cast<icalcomponent_kind>(kindIndex));
            // Just to simulate usage
            if (firstComponent) {
                const char *comment = icalcomponent_get_comment(firstComponent);
            }
        }

        // Use the icalcomponent_get_comment function
        const char *comment = icalcomponent_get_comment(component);

        // Free the component
        icalcomponent_free(component);
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

        LLVMFuzzerTestOneInput_39(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    