// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalrestriction_compare at icalrestriction.c:73:6 in icalrestriction.h
// icalrecur_expand_recurrence at icalrecur.c:4140:6 in icalrecur.h
// icalcomponent_check_restrictions at icalcomponent.c:1117:6 in icalcomponent.h
// icalcomponent_set_dtend at icalcomponent.c:1622:6 in icalcomponent.h
// icalcomponent_get_duration at icalcomponent.c:1664:25 in icalcomponent.h
// icalcomponent_get_first_real_component at icalcomponent.c:647:16 in icalcomponent.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
extern "C" {
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalrestriction.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalrecur.h"
}

#include <cstdint>
#include <cstdlib>
#include <cstring>

static icalcomponent* create_dummy_component() {
    icalcomponent* comp = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    icalcomponent* vevent = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalcomponent_add_component(comp, vevent);
    return comp;
}

static icaltimetype create_dummy_icaltimetype() {
    icaltimetype tt;
    memset(&tt, 0, sizeof(tt));
    tt.year = 2023;
    return tt;
}

static bool fuzz_icalcomponent_get_first_real_component(const uint8_t* data, size_t size) {
    icalcomponent* comp = create_dummy_component();
    icalcomponent* real_comp = icalcomponent_get_first_real_component(comp);
    bool result = (real_comp != nullptr);
    icalcomponent_free(comp);
    return result;
}

static bool fuzz_icalcomponent_set_dtend(const uint8_t* data, size_t size) {
    icalcomponent* comp = create_dummy_component();
    icaltimetype dtend = create_dummy_icaltimetype();
    icalcomponent_set_dtend(comp, dtend);
    icalcomponent_free(comp);
    return true;
}

static bool fuzz_icalrestriction_compare(const uint8_t* data, size_t size) {
    if (size < 2) return false;
    icalrestriction_kind restr = static_cast<icalrestriction_kind>(data[0] % ICAL_RESTRICTION_UNKNOWN);
    int count = data[1] % 3; // Limit count to 0, 1, 2
    return icalrestriction_compare(restr, count);
}

static bool fuzz_icalcomponent_get_duration(const uint8_t* data, size_t size) {
    icalcomponent* comp = create_dummy_component();
    icaldurationtype duration = icalcomponent_get_duration(comp);
    bool result = (duration.days >= 0);
    icalcomponent_free(comp);
    return result;
}

static bool fuzz_icalcomponent_check_restrictions(const uint8_t* data, size_t size) {
    icalcomponent* comp = create_dummy_component();
    bool result = icalcomponent_check_restrictions(comp);
    icalcomponent_free(comp);
    return result;
}

static bool fuzz_icalrecur_expand_recurrence(const uint8_t* data, size_t size) {
    if (size < 10) return false;
    const char* rule = reinterpret_cast<const char*>(data);
    icaltime_t start = {0}; // Dummy start time
    int count = data[0] % 10; // Max 10 occurrences
    icaltime_t* array = new icaltime_t[count];
    bool result = icalrecur_expand_recurrence(rule, start, count, array);
    delete[] array;
    return result;
}

extern "C" int LLVMFuzzerTestOneInput_63(const uint8_t* data, size_t size) {
    fuzz_icalcomponent_get_first_real_component(data, size);
    fuzz_icalcomponent_set_dtend(data, size);
    fuzz_icalrestriction_compare(data, size);
    fuzz_icalcomponent_get_duration(data, size);
    fuzz_icalcomponent_check_restrictions(data, size);
    fuzz_icalrecur_expand_recurrence(data, size);
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

        LLVMFuzzerTestOneInput_63(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    