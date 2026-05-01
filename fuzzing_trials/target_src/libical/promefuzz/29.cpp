// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_remove_component at icalcomponent.c:543:6 in icalcomponent.h
// icalcomponent_set_parent at icalcomponent.c:1231:6 in icalcomponent.h
// icalcomponent_get_parent at icalcomponent.c:1226:16 in icalcomponent.h
// icalcomponent_add_component at icalcomponent.c:509:6 in icalcomponent.h
// icalcomponent_new_vtimezone at icalcomponent.c:2055:16 in icalcomponent.h
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
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <icalcomponent.h>

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a new VTIMEZONE component
    icalcomponent *vtimezone = icalcomponent_new_vtimezone();
    if (!vtimezone) return 0;

    // Create another component to act as a child
    icalcomponent *child = icalcomponent_new_vtimezone();
    if (!child) {
        icalcomponent_free(vtimezone);
        return 0;
    }

    // Fuzzing logic for icalcomponent_set_parent
    icalcomponent_set_parent(child, vtimezone);

    // Fuzzing logic for icalcomponent_add_component
    icalcomponent_add_component(vtimezone, child);

    // Fuzzing logic for icalcomponent_get_parent
    icalcomponent *parent = icalcomponent_get_parent(child);
    (void)parent; // Suppress unused variable warning

    // Fuzzing logic for icalcomponent_isa
    icalcomponent_kind kind = icalcomponent_isa(vtimezone);
    (void)kind; // Suppress unused variable warning

    // Fuzzing logic for icalcomponent_remove_component
    icalcomponent_remove_component(vtimezone, child);

    // Free allocated components
    icalcomponent_free(child);
    icalcomponent_free(vtimezone);

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

        LLVMFuzzerTestOneInput_29(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    