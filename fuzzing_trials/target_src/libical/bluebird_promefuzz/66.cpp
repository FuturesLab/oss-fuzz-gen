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
#include <stdint.h>
#include <stddef.h>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_66(const uint8_t *Data, size_t Size) {
    // Fuzz icalcomponent_new_vjournal
    icalcomponent *vjournal = icalcomponent_new_vjournal();
    if (vjournal) {
        // Perform operations if needed
        icalcomponent_free(vjournal);
    }

    // Fuzz icalcomponent_new_vagenda
    icalcomponent *vagenda = icalcomponent_new_vagenda();
    if (vagenda) {
        // Perform operations if needed
        icalcomponent_free(vagenda);
    }

    // Fuzz icalcomponent_new_vlocation
    icalcomponent *vlocation = icalcomponent_new_vlocation();
    if (vlocation) {
        // Perform operations if needed
        icalcomponent_free(vlocation);
    }

    // Fuzz icalcomponent_new_valarm
    icalcomponent *valarm = icalcomponent_new_valarm();
    if (valarm) {
        // Perform operations if needed
        icalcomponent_free(valarm);
    }

    // Fuzz icalcomponent_new_vresource
    icalcomponent *vresource = icalcomponent_new_vresource();
    if (vresource) {
        // Perform operations if needed
        icalcomponent_free(vresource);
    }

    // Fuzz icalcomponent_new_vquery
    icalcomponent *vquery = icalcomponent_new_vquery();
    if (vquery) {
        // Perform operations if needed
        icalcomponent_free(vquery);
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

    LLVMFuzzerTestOneInput_66(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
