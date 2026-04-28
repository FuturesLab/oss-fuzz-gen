// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_new_vtodo at icalcomponent.c:2035:16 in icalcomponent.h
// icalcomponent_normalize at icalcomponent.c:2832:6 in icalcomponent.h
// icalcomponent_new_vavailability at icalcomponent.c:2085:16 in icalcomponent.h
// icalcomponent_new_vagenda at icalcomponent.c:2070:16 in icalcomponent.h
// icalcomponent_clone at icalcomponent.c:129:16 in icalcomponent.h
// icalcomponent_new_vcalendar at icalcomponent.c:2025:16 in icalcomponent.h
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
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    // Create various ical components
    icalcomponent *vcalendar = icalcomponent_new_vcalendar();
    icalcomponent *vagenda = icalcomponent_new_vagenda();
    icalcomponent *vavailability = icalcomponent_new_vavailability();
    icalcomponent *vtodo = icalcomponent_new_vtodo();

    // Clone the components if they are not NULL
    icalcomponent *cloned_vcalendar = vcalendar ? icalcomponent_clone(vcalendar) : NULL;
    icalcomponent *cloned_vagenda = vagenda ? icalcomponent_clone(vagenda) : NULL;
    icalcomponent *cloned_vavailability = vavailability ? icalcomponent_clone(vavailability) : NULL;
    icalcomponent *cloned_vtodo = vtodo ? icalcomponent_clone(vtodo) : NULL;

    // Normalize the components
    if (vcalendar) icalcomponent_normalize(vcalendar);
    if (vagenda) icalcomponent_normalize(vagenda);
    if (vavailability) icalcomponent_normalize(vavailability);
    if (vtodo) icalcomponent_normalize(vtodo);

    // Cleanup: free the components
    if (vcalendar) icalcomponent_free(vcalendar);
    if (vagenda) icalcomponent_free(vagenda);
    if (vavailability) icalcomponent_free(vavailability);
    if (vtodo) icalcomponent_free(vtodo);

    if (cloned_vcalendar) icalcomponent_free(cloned_vcalendar);
    if (cloned_vagenda) icalcomponent_free(cloned_vagenda);
    if (cloned_vavailability) icalcomponent_free(cloned_vavailability);
    if (cloned_vtodo) icalcomponent_free(cloned_vtodo);

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
    