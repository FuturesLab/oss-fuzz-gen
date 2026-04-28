// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_set_duration at icalcomponent.c:1647:6 in icalcomponent.h
// icalcomponent_get_duration at icalcomponent.c:1664:25 in icalcomponent.h
// icaldurationtype_bad_duration at icalduration.c:278:25 in icalduration.h
// icaldurationtype_normalize at icalduration.c:364:25 in icalduration.h
// icaldurationtype_null_duration at icalduration.c:256:25 in icalduration.h
// icaldurationtype_from_string at icalduration.c:38:25 in icalduration.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalduration.h"

extern "C" int LLVMFuzzerTestOneInput_54(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Test icaldurationtype_normalize
    struct icaldurationtype dur;
    dur.is_neg = Data[0] % 2;
    dur.days = Data[0];
    dur.hours = Data[0] % 24;
    dur.minutes = Data[0] % 60;
    dur.seconds = Data[0] % 60;
    struct icaldurationtype normalized = icaldurationtype_normalize(dur);

    // Test icaldurationtype_null_duration
    struct icaldurationtype null_duration = icaldurationtype_null_duration();
    assert(null_duration.days == 0);
    assert(null_duration.weeks == 0);
    assert(null_duration.hours == 0);
    assert(null_duration.minutes == 0);
    assert(null_duration.seconds == 0);
    assert(icaldurationtype_is_null_duration(null_duration));
    assert(icaldurationtype_as_seconds(null_duration) == 0);

    // Test icaldurationtype_bad_duration
    struct icaldurationtype bad_duration = icaldurationtype_bad_duration();
    assert(icaldurationtype_is_bad_duration(bad_duration));

    // Test icaldurationtype_from_string
    // Ensure null-terminated string for icaldurationtype_from_string
    std::string input_str(reinterpret_cast<const char*>(Data), Size);
    struct icaldurationtype from_string = icaldurationtype_from_string(input_str.c_str());
    if (icaldurationtype_is_bad_duration(from_string)) {
        assert(icalerrno == ICAL_MALFORMEDDATA_ERROR);
    }

    // Test icalcomponent_set_duration and icalcomponent_get_duration
    icalcomponent *comp = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalcomponent_set_duration(comp, normalized);
    struct icaldurationtype retrieved_duration = icalcomponent_get_duration(comp);
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

        if(size < 1 + 1)
            exit(0);

        data = (uint8_t *)malloc((size_t)size);
        if(data == NULL)
            exit(0);

        if(fread(data, (size_t)size, 1, f) != 1)
            exit(0);

        LLVMFuzzerTestOneInput_54(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    