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
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalcomponent.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icaltimezone.h"

static icalcomponent* create_dummy_component() {
    icalcomponent* comp = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    if (!comp) {
        return nullptr;
    }
    icaltimezone* tz = icaltimezone_new();
    if (!tz) {
        icalcomponent_free(comp);
        return nullptr;
    }
    icalcomponent* vtimezone = icalcomponent_new(ICAL_VTIMEZONE_COMPONENT);
    icaltimezone_set_component(tz, vtimezone);
    icalcomponent_add_component(comp, vtimezone);
    return comp;
}

extern "C" int LLVMFuzzerTestOneInput_364(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare a dummy icalcomponent
    icalcomponent* comp = create_dummy_component();
    if (!comp) return 0;

    // Prepare a dummy icaltimetype
    struct icaltimetype tt;
    memset(&tt, 0, sizeof(tt));

    // Prepare a timezone
    icaltimezone* from_zone = icaltimezone_new();
    icaltimezone* to_zone = icaltimezone_get_utc_timezone();

    // Convert time
    icaltimezone_convert_time(&tt, from_zone, to_zone);

    // Get timezone from component
    char tzid[256];
    size_t tzid_len = std::min(Size, sizeof(tzid) - 1);
    memcpy(tzid, Data, tzid_len);
    tzid[tzid_len] = '\0';
    icaltimezone* tz = icalcomponent_get_timezone(comp, tzid);

    // Get component from timezone
    icalcomponent* tz_comp = icaltimezone_get_component(tz);

    // Set component to timezone
    bool set_result = icaltimezone_set_component(from_zone, comp);

    // Clean up
    icalcomponent_free(comp);
    icaltimezone_free(from_zone, 1);

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

    LLVMFuzzerTestOneInput_364(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
