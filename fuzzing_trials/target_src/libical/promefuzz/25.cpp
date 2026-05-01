// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_new_vlocation at icalcomponent.c:2125:16 in icalcomponent.h
// icalcomponent_new_vreply at icalcomponent.c:2080:16 in icalcomponent.h
// icalcomponent_new_valarm at icalcomponent.c:2045:16 in icalcomponent.h
// icalcomponent_new_vcalendar at icalcomponent.c:2025:16 in icalcomponent.h
// icalcomponent_new_vresource at icalcomponent.c:2130:16 in icalcomponent.h
// icalcomponent_new_vfreebusy at icalcomponent.c:2050:16 in icalcomponent.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
extern "C" {
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"
}

#include <cstdint>
#include <cstdlib>

static void cleanup(icalcomponent *component) {
    if (component) {
        icalcomponent_free(component);
    }
}

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create components based on the first byte of the input data
    icalcomponent *component = nullptr;
    switch (Data[0] % 6) {
        case 0:
            component = icalcomponent_new_vfreebusy();
            break;
        case 1:
            component = icalcomponent_new_vreply();
            break;
        case 2:
            component = icalcomponent_new_vresource();
            break;
        case 3:
            component = icalcomponent_new_vlocation();
            break;
        case 4:
            component = icalcomponent_new_valarm();
            break;
        case 5:
            component = icalcomponent_new_vcalendar();
            break;
        default:
            break;
    }

    // Cleanup the created component
    cleanup(component);

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

        LLVMFuzzerTestOneInput_25(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    