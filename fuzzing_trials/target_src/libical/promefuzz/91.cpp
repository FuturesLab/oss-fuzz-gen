// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_isa at icalcomponent.c:304:20 in icalcomponent.h
// icalcomponent_get_next_component at icalcomponent.c:627:16 in icalcomponent.h
// icalcomponent_get_first_component at icalcomponent.c:611:16 in icalcomponent.h
// icalcomponent_get_current_component at icalcomponent.c:600:16 in icalcomponent.h
// icalcomponent_get_parent at icalcomponent.c:1226:16 in icalcomponent.h
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
#include <cstdint>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_91(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(icalcomponent_kind)) {
        return 0;
    }

    // Create a dummy icalcomponent for testing
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);

    // Extract a kind from the input data
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES);

    // Test icalcomponent_get_first_component
    icalcomponent *first_component = icalcomponent_get_first_component(component, kind);
    if (first_component) {
        // Test icalcomponent_get_next_component
        icalcomponent *next_component = icalcomponent_get_next_component(component, kind);
        (void)next_component; // Suppress unused variable warning
    }

    // Test icalcomponent_get_current_component
    icalcomponent *current_component = icalcomponent_get_current_component(component);
    (void)current_component; // Suppress unused variable warning

    // Test icalcomponent_get_parent
    const icalcomponent *parent_component = icalcomponent_get_parent(component);
    (void)parent_component; // Suppress unused variable warning

    // Test icalcomponent_isa
    icalcomponent_kind component_kind = icalcomponent_isa(component);
    (void)component_kind; // Suppress unused variable warning

    // Test icalcomponent_get_inner
    icalcomponent *inner_component = icalcomponent_get_inner(component);
    (void)inner_component; // Suppress unused variable warning

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

        LLVMFuzzerTestOneInput_91(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    