// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icallangbind_get_next_component at icallangbind.c:117:16 in icallangbind.h
// icalcomponent_get_relcalid at icalcomponent.c:2591:13 in icalcomponent.h
// icalcomponent_as_ical_string_r at icalcomponent.c:226:7 in icalcomponent.h
// icalcomponent_set_uid at icalcomponent.c:1804:6 in icalcomponent.h
// icalcomponent_get_summary at icalcomponent.c:1746:13 in icalcomponent.h
// icalcomponent_new_from_string at icalcomponent.c:124:16 in icalcomponent.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icallangbind.h"

extern "C" int LLVMFuzzerTestOneInput_133(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Ensure the data is null-terminated
    char *inputData = static_cast<char *>(malloc(Size + 1));
    if (!inputData) {
        return 0;
    }
    memcpy(inputData, Data, Size);
    inputData[Size] = '\0';

    // Create an icalcomponent from the input string
    icalcomponent *component = icalcomponent_new_from_string(inputData);
    if (component) {
        // Test icalcomponent_as_ical_string_r
        char *icalString = icalcomponent_as_ical_string_r(component);
        if (icalString) {
            free(icalString);
        }

        // Test icalcomponent_get_summary
        const char *summary = icalcomponent_get_summary(component);

        // Test icalcomponent_get_relcalid
        const char *relcalid = icalcomponent_get_relcalid(component);

        // Test icalcomponent_set_uid
        icalcomponent_set_uid(component, "test-uid");

        // Test icallangbind_get_next_component
        icalcomponent *nextComponent = icallangbind_get_next_component(component, "VEVENT");
        if (nextComponent) {
            // Do something with nextComponent if needed
        }

        // Free the component
        icalcomponent_free(component);
    }

    free(inputData);
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

        LLVMFuzzerTestOneInput_133(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    