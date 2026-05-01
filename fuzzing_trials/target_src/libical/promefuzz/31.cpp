// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_get_method at icalcomponent.c:1511:21 in icalcomponent.h
// icalcomponent_set_method at icalcomponent.c:1499:6 in icalcomponent.h
// icalcomponent_new_vreply at icalcomponent.c:2080:16 in icalcomponent.h
// icalcomponent_new_vagenda at icalcomponent.c:2070:16 in icalcomponent.h
// icalcomponent_new_vevent at icalcomponent.c:2030:16 in icalcomponent.h
// icalcomponent_new_vtodo at icalcomponent.c:2035:16 in icalcomponent.h
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
#include <iostream>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create various icalcomponent types
    icalcomponent *vtodo = icalcomponent_new_vtodo();
    icalcomponent *vevent = icalcomponent_new_vevent();
    icalcomponent *vreply = icalcomponent_new_vreply();
    icalcomponent *vagenda = icalcomponent_new_vagenda();

    // Choose a method based on the input data
    icalproperty_method method = static_cast<icalproperty_method>(Data[0] % 17 + 10500);

    // Set methods to components
    icalcomponent_set_method(vtodo, method);
    icalcomponent_set_method(vevent, method);
    icalcomponent_set_method(vreply, method);
    icalcomponent_set_method(vagenda, method);

    // Retrieve methods to ensure they are set correctly
    icalcomponent_get_method(vtodo);
    icalcomponent_get_method(vevent);
    icalcomponent_get_method(vreply);
    icalcomponent_get_method(vagenda);

    // Clean up
    icalcomponent_free(vtodo);
    icalcomponent_free(vevent);
    icalcomponent_free(vreply);
    icalcomponent_free(vagenda);

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

        LLVMFuzzerTestOneInput_31(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    