// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_new_vtimezone at icalcomponent.c:2055:16 in icalcomponent.h
// icalcomponent_remove_component at icalcomponent.c:543:6 in icalcomponent.h
// icalcomponent_get_parent at icalcomponent.c:1226:16 in icalcomponent.h
// icalcomponent_add_component at icalcomponent.c:509:6 in icalcomponent.h
// icalcomponent_set_parent at icalcomponent.c:1231:6 in icalcomponent.h
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

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    icalcomponent *parent = icalcomponent_new_vtimezone();
    icalcomponent *child = icalcomponent_new_vtimezone();

    // Fuzzing icalcomponent_set_parent
    icalcomponent_set_parent(child, parent);

    // Fuzzing icalcomponent_add_component
    icalcomponent_add_component(parent, child);

    // Fuzzing icalcomponent_get_parent
    icalcomponent *retrieved_parent = icalcomponent_get_parent(child);
    if (retrieved_parent != parent) {
        // Handle error case
    }

    // Fuzzing icalcomponent_isa
    icalcomponent_kind kind = icalcomponent_isa(child);
    if (kind != ICAL_VTIMEZONE_COMPONENT) {
        // Handle error case
    }

    // Fuzzing icalcomponent_remove_component
    icalcomponent_remove_component(parent, child);

    // Clean up
    icalcomponent_free(child);
    icalcomponent_free(parent);

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

        LLVMFuzzerTestOneInput_26(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    