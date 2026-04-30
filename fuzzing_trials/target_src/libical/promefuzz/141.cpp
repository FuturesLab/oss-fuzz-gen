// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_new at icalcomponent.c:100:16 in icalcomponent.h
// icalcomponent_vanew at icalcomponent.c:105:16 in icalcomponent.h
// icalcomponent_new_xpatch at icalcomponent.c:2115:16 in icalcomponent.h
// icalcomponent_new_vresource at icalcomponent.c:2130:16 in icalcomponent.h
// icalcomponent_new_vlocation at icalcomponent.c:2125:16 in icalcomponent.h
// icalcomponent_new_xavailable at icalcomponent.c:2090:16 in icalcomponent.h
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
#include <iostream>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"

static void fuzz_icalcomponent_new_xpatch() {
    icalcomponent *comp = icalcomponent_new_xpatch();
    if (comp) {
        // Perform operations with comp if needed
        icalcomponent_free(comp);
    }
}

static void fuzz_icalcomponent_new_vlocation() {
    icalcomponent *comp = icalcomponent_new_vlocation();
    if (comp) {
        // Perform operations with comp if needed
        icalcomponent_free(comp);
    }
}

static void fuzz_icalcomponent_new(icalcomponent_kind kind) {
    icalcomponent *comp = icalcomponent_new(kind);
    if (comp) {
        // Perform operations with comp if needed
        icalcomponent_free(comp);
    }
}

static void fuzz_icalcomponent_new_vresource() {
    icalcomponent *comp = icalcomponent_new_vresource();
    if (comp) {
        // Perform operations with comp if needed
        icalcomponent_free(comp);
    }
}

static void fuzz_icalcomponent_vanew(icalcomponent_kind kind) {
    icalcomponent *child = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalcomponent *comp = icalcomponent_vanew(kind, child, NULL);
    if (comp) {
        // Perform operations with comp if needed
        icalcomponent_free(comp);
    }
}

static void fuzz_icalcomponent_new_xavailable() {
    icalcomponent *comp = icalcomponent_new_xavailable();
    if (comp) {
        // Perform operations with comp if needed
        icalcomponent_free(comp);
    }
}

extern "C" int LLVMFuzzerTestOneInput_141(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    fuzz_icalcomponent_new_xpatch();
    fuzz_icalcomponent_new_vlocation();

    icalcomponent_kind kind = static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES);
    fuzz_icalcomponent_new(kind);
    fuzz_icalcomponent_new_vresource();
    fuzz_icalcomponent_vanew(kind);
    fuzz_icalcomponent_new_xavailable();

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

        LLVMFuzzerTestOneInput_141(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    