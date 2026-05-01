// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_new_vquery at icalcomponent.c:2075:16 in icalcomponent.h
// icalcomponent_new_vjournal at icalcomponent.c:2040:16 in icalcomponent.h
// icalcomponent_new_vcalendar at icalcomponent.c:2025:16 in icalcomponent.h
// icalcomponent_new_vresource at icalcomponent.c:2130:16 in icalcomponent.h
// icalcomponent_new_vagenda at icalcomponent.c:2070:16 in icalcomponent.h
// icalcomponent_new_xpatch at icalcomponent.c:2115:16 in icalcomponent.h
#include <cstdint>
extern "C" {
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"
}

extern "C" int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Fuzzing icalcomponent_new_vquery
    icalcomponent *vquery_component = icalcomponent_new_vquery();
    if (vquery_component != nullptr) {
        // Clean up
        icalcomponent_free(vquery_component);
    }

    // Fuzzing icalcomponent_new_vresource
    icalcomponent *vresource_component = icalcomponent_new_vresource();
    if (vresource_component != nullptr) {
        // Clean up
        icalcomponent_free(vresource_component);
    }

    // Fuzzing icalcomponent_new_vjournal
    icalcomponent *vjournal_component = icalcomponent_new_vjournal();
    if (vjournal_component != nullptr) {
        // Clean up
        icalcomponent_free(vjournal_component);
    }

    // Fuzzing icalcomponent_new_vagenda
    icalcomponent *vagenda_component = icalcomponent_new_vagenda();
    if (vagenda_component != nullptr) {
        // Clean up
        icalcomponent_free(vagenda_component);
    }

    // Fuzzing icalcomponent_new_vcalendar
    icalcomponent *vcalendar_component = icalcomponent_new_vcalendar();
    if (vcalendar_component != nullptr) {
        // Clean up
        icalcomponent_free(vcalendar_component);
    }

    // Fuzzing icalcomponent_new_xpatch
    icalcomponent *xpatch_component = icalcomponent_new_xpatch();
    if (xpatch_component != nullptr) {
        // Clean up
        icalcomponent_free(xpatch_component);
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

        LLVMFuzzerTestOneInput_46(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    