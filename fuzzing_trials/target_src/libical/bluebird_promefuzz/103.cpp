#include <sys/stat.h>
#include <string.h>
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
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_103(const uint8_t *Data, size_t Size) {
    // Step 1: Prepare the environment and create components
    icalcomponent *vtimezone = icalcomponent_new_vtimezone();
    icalcomponent *vavailability = icalcomponent_new_vavailability();
    icalcomponent *vevent = icalcomponent_new_vevent();
    icalcomponent *vtodo = icalcomponent_new_vtodo();
    icalcomponent *xavailable = icalcomponent_new_xavailable();

    // Step 2: Perform operations on the components
    if (vtimezone) {
        icaltime_span span = icalcomponent_get_span(vtimezone);
    }
    if (vavailability) {
        icaltime_span span = icalcomponent_get_span(vavailability);
    }
    if (vevent) {
        icaltime_span span = icalcomponent_get_span(vevent);
    }
    if (vtodo) {
        icaltime_span span = icalcomponent_get_span(vtodo);
    }
    if (xavailable) {
        icaltime_span span = icalcomponent_get_span(xavailable);
    }

    // Step 3: Cleanup
    if (vtimezone) {
        icalcomponent_free(vtimezone);
    }
    if (vavailability) {
        icalcomponent_free(vavailability);
    }
    if (vevent) {
        icalcomponent_free(vevent);
    }
    if (vtodo) {
        icalcomponent_free(vtodo);
    }
    if (xavailable) {
        icalcomponent_free(xavailable);
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_103(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
