// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_vanew at icalcomponent.c:105:16 in icalcomponent.h
// icalcomponent_new at icalcomponent.c:100:16 in icalcomponent.h
// icalcomponent_new_xpatch at icalcomponent.c:2115:16 in icalcomponent.h
// icalcomponent_new_xvote at icalcomponent.c:2105:16 in icalcomponent.h
// icalcomponent_new_vpatch at icalcomponent.c:2110:16 in icalcomponent.h
// icalcomponent_new_vlocation at icalcomponent.c:2125:16 in icalcomponent.h
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
#include <cstdarg>
#include <cstdlib>
#include <iostream>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_143(const uint8_t *Data, size_t Size) {
    // Fuzz icalcomponent_new_xpatch
    icalcomponent *xpatch_component = icalcomponent_new_xpatch();
    if (xpatch_component) {
        // Simulate some operations on the component
        icalcomponent_free(xpatch_component);
    }

    // Fuzz icalcomponent_new_vlocation
    icalcomponent *vlocation_component = icalcomponent_new_vlocation();
    if (vlocation_component) {
        // Simulate some operations on the component
        icalcomponent_free(vlocation_component);
    }

    // Fuzz icalcomponent_new with different kinds
    if (Size > 0) {
        icalcomponent_kind kind = static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES);
        icalcomponent *component = icalcomponent_new(kind);
        if (component) {
            // Simulate some operations on the component
            icalcomponent_free(component);
        }
    }

    // Fuzz icalcomponent_new_vpatch
    icalcomponent *vpatch_component = icalcomponent_new_vpatch();
    if (vpatch_component) {
        // Simulate some operations on the component
        icalcomponent_free(vpatch_component);
    }

    // Fuzz icalcomponent_new_xvote
    icalcomponent *xvote_component = icalcomponent_new_xvote();
    if (xvote_component) {
        // Simulate some operations on the component
        icalcomponent_free(xvote_component);
    }

    // Fuzz icalcomponent_vanew with different kinds and null-terminated arguments
    if (Size > 1) {
        icalcomponent_kind kind = static_cast<icalcomponent_kind>(Data[1] % ICAL_NUM_COMPONENT_TYPES);
        icalcomponent *child_component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
        if (child_component) {
            icalcomponent *vanew_component = icalcomponent_vanew(kind, child_component, nullptr);
            if (vanew_component) {
                // Simulate some operations on the component
                icalcomponent_free(vanew_component);
            }
            // No need to free child_component separately, as vanew_component takes ownership
        }
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

        LLVMFuzzerTestOneInput_143(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    