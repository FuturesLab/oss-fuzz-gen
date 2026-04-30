// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_new_vevent at icalcomponent.c:2030:16 in icalcomponent.h
// icalcomponent_new_vtodo at icalcomponent.c:2035:16 in icalcomponent.h
// icalcomponent_new_vagenda at icalcomponent.c:2070:16 in icalcomponent.h
// icalcomponent_new_vresource at icalcomponent.c:2130:16 in icalcomponent.h
// icalcomponent_new_vcalendar at icalcomponent.c:2025:16 in icalcomponent.h
// icalcomponent_free at icalcomponent.c:172:6 in icalcomponent.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstddef>
#include <cstdint>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <icalcomponent.h>

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    // Create various icalcomponent objects
    icalcomponent *vtodo = icalcomponent_new_vtodo();
    icalcomponent *vevent = icalcomponent_new_vevent();
    icalcomponent *vresource = icalcomponent_new_vresource();
    icalcomponent *vagenda = icalcomponent_new_vagenda();
    icalcomponent *vcalendar = icalcomponent_new_vcalendar();

    // Free the components
    if (vtodo) {
        icalcomponent_free(vtodo);
    }
    if (vevent) {
        icalcomponent_free(vevent);
    }
    if (vresource) {
        icalcomponent_free(vresource);
    }
    if (vagenda) {
        icalcomponent_free(vagenda);
    }
    if (vcalendar) {
        icalcomponent_free(vcalendar);
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

        LLVMFuzzerTestOneInput_1(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    