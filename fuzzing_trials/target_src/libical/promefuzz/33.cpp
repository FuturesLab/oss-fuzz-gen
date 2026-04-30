// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_new_xpatch at icalcomponent.c:2115:16 in icalcomponent.h
// icalcomponent_get_parent at icalcomponent.c:1226:16 in icalcomponent.h
// icalcomponent_new_vlocation at icalcomponent.c:2125:16 in icalcomponent.h
// icalcomponent_new_xavailable at icalcomponent.c:2090:16 in icalcomponent.h
// icalcomponent_new_vevent at icalcomponent.c:2030:16 in icalcomponent.h
// icalcomponent_new_vresource at icalcomponent.c:2130:16 in icalcomponent.h
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
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <icalcomponent.h>

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size) {
    // Create various components using the target functions
    icalcomponent *xpatch_component = icalcomponent_new_xpatch();
    icalcomponent *vlocation_component = icalcomponent_new_vlocation();
    icalcomponent *vevent_component = icalcomponent_new_vevent();
    icalcomponent *vresource_component = icalcomponent_new_vresource();
    icalcomponent *xavailable_component = icalcomponent_new_xavailable();

    // Attempt to get the parent of each component
    icalcomponent *parent_xpatch = icalcomponent_get_parent(xpatch_component);
    icalcomponent *parent_vlocation = icalcomponent_get_parent(vlocation_component);
    icalcomponent *parent_vevent = icalcomponent_get_parent(vevent_component);
    icalcomponent *parent_vresource = icalcomponent_get_parent(vresource_component);
    icalcomponent *parent_xavailable = icalcomponent_get_parent(xavailable_component);

    // Clean up by freeing the components
    if (xpatch_component) {
        icalcomponent_free(xpatch_component);
    }
    if (vlocation_component) {
        icalcomponent_free(vlocation_component);
    }
    if (vevent_component) {
        icalcomponent_free(vevent_component);
    }
    if (vresource_component) {
        icalcomponent_free(vresource_component);
    }
    if (xavailable_component) {
        icalcomponent_free(xavailable_component);
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

        LLVMFuzzerTestOneInput_33(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    