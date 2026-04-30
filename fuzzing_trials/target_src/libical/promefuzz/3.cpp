// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcompiter_next at icalcomponent.c:1387:16 in icalcomponent.h
// icalcompiter_deref at icalcomponent.c:1425:16 in icalcomponent.h
// icalcompiter_prior at icalcomponent.c:1406:16 in icalcomponent.h
// icalcomponent_get_first_component at icalcomponent.c:611:16 in icalcomponent.h
// icalcomponent_end_component at icalcomponent.c:1365:14 in icalcomponent.h
// icalcomponent_begin_component at icalcomponent.c:1342:14 in icalcomponent.h
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
#include <fstream>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(icalcomponent_kind)) {
        return 0;
    }

    // Create a dummy icalcomponent for fuzzing purposes
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    if (!component) {
        return 0;
    }

    // Extract icalcomponent_kind from the input data
    icalcomponent_kind kind;
    std::memcpy(&kind, Data, sizeof(icalcomponent_kind));

    // Begin component iteration
    icalcompiter iter = icalcomponent_begin_component(component, kind);
    icalcomponent *comp = icalcompiter_deref(&iter);

    // Iterate through components using next
    while ((comp = icalcompiter_next(&iter)) != nullptr) {
        // Process component
    }

    // End component iteration
    iter = icalcomponent_end_component(component, kind);
    comp = icalcompiter_deref(&iter);

    // Iterate backward through components using prior
    while ((comp = icalcompiter_prior(&iter)) != nullptr) {
        // Process component
    }

    // Get first component of specified kind
    comp = icalcomponent_get_first_component(component, kind);

    // Cleanup
    icalcomponent_free(component);

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

        LLVMFuzzerTestOneInput_3(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    