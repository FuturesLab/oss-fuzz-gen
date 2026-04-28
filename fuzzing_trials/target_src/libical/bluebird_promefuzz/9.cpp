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
#include <cstring>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalcomponent.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalvalue.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalduration.h"

static icaltimetype random_icaltimetype(const uint8_t *Data, size_t &offset, size_t Size) {
    icaltimetype time;
    if (offset + sizeof(int) <= Size) {
        memcpy(&time.year, Data + offset, sizeof(int));
        offset += sizeof(int);
    } else {
        time.year = 2023; // Default year
    }
    time.zone = nullptr; // Simplification for fuzzing
    return time;
}

static icaldurationtype random_icaldurationtype(const uint8_t *Data, size_t &offset, size_t Size) {
    icaldurationtype duration;
    if (offset < Size) {
        duration.is_neg = Data[offset] % 2;
        offset++;
    } else {
        duration.is_neg = 0;
    }
    if (offset + sizeof(unsigned int) <= Size) {
        memcpy(&duration.days, Data + offset, sizeof(unsigned int));
        offset += sizeof(unsigned int);
    } else {
        duration.days = 1; // Default days
    }
    return duration;
}

static icalcomponent* random_icalcomponent(const uint8_t *Data, size_t &offset, size_t Size) {
    icalcomponent_kind kind = ICAL_VTODO_COMPONENT;
    if (offset < Size) {
        kind = static_cast<icalcomponent_kind>(Data[offset] % ICAL_NUM_COMPONENT_TYPES);
        offset++;
    }
    return icalcomponent_new(kind);
}

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    size_t offset = 0;

    // Fuzz icalduration_extend
    icaltimetype time = random_icaltimetype(Data, offset, Size);
    icaldurationtype duration = random_icaldurationtype(Data, offset, Size);
    icaltimetype new_time = icalduration_extend(time, duration);

    // Fuzz icalcomponent_set_due
    icalcomponent *comp = random_icalcomponent(Data, offset, Size);
    icalcomponent_set_due(comp, new_time);

    // Fuzz print_datetime_to_string
    char datetime_str[100] = {0};
    print_datetime_to_string(datetime_str, &new_time);

    // Fuzz icalcomponent_set_dtstamp
    icalcomponent_set_dtstamp(comp, new_time);

    // Fuzz print_date_to_string
    char date_str[100] = {0};
    print_date_to_string(date_str, &new_time);

    // Fuzz icalcomponent_set_recurrenceid
    icalcomponent_set_recurrenceid(comp, new_time);

    // Cleanup
    icalcomponent_free(comp);

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

    LLVMFuzzerTestOneInput_9(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
