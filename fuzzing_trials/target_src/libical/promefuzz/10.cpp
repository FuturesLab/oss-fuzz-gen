// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_isa_component at icalcomponent.c:311:6 in icalcomponent.h
// icalcomponent_kind_is_valid at icalcomponent.c:1293:6 in icalcomponent.h
// icalcomponent_is_valid at icalcomponent.c:295:6 in icalcomponent.h
// icalcomponent_new_from_string at icalcomponent.c:124:16 in icalcomponent.h
// icalcomponent_set_description at icalcomponent.c:1885:6 in icalcomponent.h
// icalproperty_recurrence_is_excluded at icalcomponent.c:738:6 in icalcomponent.h
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
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Ensure null-terminated string for icalcomponent_new_from_string
    char *icalStr = static_cast<char*>(malloc(Size + 1));
    if (!icalStr) return 0;
    memcpy(icalStr, Data, Size);
    icalStr[Size] = '\0';

    // Create icalcomponent from string
    icalcomponent *comp = icalcomponent_new_from_string(icalStr);
    free(icalStr);

    if (comp) {
        // Test icalcomponent_isa_component
        icalcomponent_isa_component(comp);

        // Setup a dummy icaltimetype for testing
        struct icaltimetype dtstart = {0};
        struct icaltimetype recurtime = {0};

        // Test icalproperty_recurrence_is_excluded
        icalproperty_recurrence_is_excluded(comp, &dtstart, &recurtime);

        // Test icalcomponent_set_description
        icalcomponent_set_description(comp, "Sample Description");

        // Test icalcomponent_kind_is_valid
        icalcomponent_kind kind = icalcomponent_isa(comp);
        icalcomponent_kind_is_valid(kind);

        // Test icalcomponent_is_valid
        icalcomponent_is_valid(comp);

        // Cleanup the component
        icalcomponent_free(comp);
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

        LLVMFuzzerTestOneInput_10(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    