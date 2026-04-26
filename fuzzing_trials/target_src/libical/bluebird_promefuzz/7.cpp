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
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalcomponent.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icaltimezone.h"

static void fuzz_icalcomponent_set_dtend(icalcomponent *comp, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(icaltimetype)) return;
    icaltimetype dtend;
    std::memcpy(&dtend, Data, sizeof(icaltimetype));
    dtend.zone = nullptr;  // Ensure the timezone is null to avoid dereferencing high-value addresses
    icalcomponent_set_dtend(comp, dtend);
}

static void fuzz_icalproperty_get_datetime_with_component(icalproperty *prop, icalcomponent *comp) {
    icaltimetype result = icalproperty_get_datetime_with_component(prop, comp);
    // Check if result is null time
    if (icaltime_is_null_time(result)) {
        std::cerr << "Null time detected" << std::endl;
    }
}

static void fuzz_icalcomponent_get_dtstart(icalcomponent *comp) {
    icaltimetype dtstart = icalcomponent_get_dtstart(comp);
    // Check if dtstart is null time
    if (icaltime_is_null_time(dtstart)) {
        std::cerr << "Null time detected" << std::endl;
    }
}

static void fuzz_icalcomponent_set_dtstart(icalcomponent *comp, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(icaltimetype)) return;
    icaltimetype dtstart;
    std::memcpy(&dtstart, Data, sizeof(icaltimetype));
    dtstart.zone = nullptr;  // Ensure the timezone is null
    icalcomponent_set_dtstart(comp, dtstart);
}

static void fuzz_icaltimezone_truncate_vtimezone(icalcomponent *vtz, const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(icaltimetype) + sizeof(bool)) return;
    icaltimetype start, end;
    bool ms_compatible;
    std::memcpy(&start, Data, sizeof(icaltimetype));
    std::memcpy(&end, Data + sizeof(icaltimetype), sizeof(icaltimetype));
    std::memcpy(&ms_compatible, Data + 2 * sizeof(icaltimetype), sizeof(bool));
    start.zone = nullptr;  // Ensure the timezone is null
    end.zone = nullptr;    // Ensure the timezone is null
    icaltimezone_truncate_vtimezone(vtz, start, end, ms_compatible);
}

static void fuzz_icalcomponent_set_due(icalcomponent *comp, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(icaltimetype)) return;
    icaltimetype due;
    std::memcpy(&due, Data, sizeof(icaltimetype));
    due.zone = nullptr;  // Ensure the timezone is null
    icalcomponent_set_due(comp, due);
}

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    // Create a dummy component for testing
    icalcomponent *comp = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalproperty *prop = icalproperty_new(ICAL_DTSTART_PROPERTY);

    // Fuzz each function with the input data
    fuzz_icalcomponent_set_dtend(comp, Data, Size);
    fuzz_icalproperty_get_datetime_with_component(prop, comp);
    fuzz_icalcomponent_get_dtstart(comp);
    fuzz_icalcomponent_set_dtstart(comp, Data, Size);
    fuzz_icaltimezone_truncate_vtimezone(comp, Data, Size);
    fuzz_icalcomponent_set_due(comp, Data, Size);

    // Clean up
    icalcomponent_free(comp);
    icalproperty_free(prop);

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

    LLVMFuzzerTestOneInput_7(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
