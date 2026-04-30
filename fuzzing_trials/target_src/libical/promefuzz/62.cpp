// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icaldurationtype_as_ical_string_r at icalduration.c:185:7 in icalduration.h
// icaldurationtype_as_ical_string at icalduration.c:176:7 in icalduration.h
// icaldurationtype_from_string at icalduration.c:38:25 in icalduration.h
// icaldurationtype_bad_duration at icalduration.c:278:25 in icalduration.h
// icaldurationtype_normalize at icalduration.c:364:25 in icalduration.h
// icaldurationtype_null_duration at icalduration.c:256:25 in icalduration.h
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
#include "icalduration.h"
}

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>

static void fuzz_icaldurationtype_normalize(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(struct icaldurationtype)) return;

    struct icaldurationtype dur;
    memcpy(&dur, Data, sizeof(struct icaldurationtype));

    struct icaldurationtype normalized = icaldurationtype_normalize(dur);

    assert(normalized.minutes <= 59);
    assert(normalized.seconds <= 59);
}

static void fuzz_icaldurationtype_null_duration() {
    struct icaldurationtype duration = icaldurationtype_null_duration();

    assert(duration.days == 0);
    assert(duration.weeks == 0);
    assert(duration.hours == 0);
    assert(duration.minutes == 0);
    assert(duration.seconds == 0);
    assert(icaldurationtype_is_null_duration(duration));
    assert(icaldurationtype_as_seconds(duration) == 0);
}

static void fuzz_icaldurationtype_as_ical_string_r(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(struct icaldurationtype)) return;

    struct icaldurationtype dur;
    memcpy(&dur, Data, sizeof(struct icaldurationtype));

    char *ical_string = icaldurationtype_as_ical_string_r(dur);

    assert(ical_string != nullptr);
}

static void fuzz_icaldurationtype_as_ical_string(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(struct icaldurationtype)) return;

    struct icaldurationtype dur;
    memcpy(&dur, Data, sizeof(struct icaldurationtype));

    char *ical_string = icaldurationtype_as_ical_string(dur);

    assert(ical_string != nullptr);

    // Do not free the string here, as it might be managed internally
    // icalmemory_free_buffer(ical_string);
}

static void fuzz_icaldurationtype_bad_duration() {
    struct icaldurationtype duration = icaldurationtype_bad_duration();

    assert(icaldurationtype_is_bad_duration(duration));
}

static void fuzz_icaldurationtype_from_string(const uint8_t *Data, size_t Size) {
    if (Size == 0) return;

    char *str = new char[Size + 1];
    memcpy(str, Data, Size);
    str[Size] = '\0';

    struct icaldurationtype duration = icaldurationtype_from_string(str);

    if (icaldurationtype_is_bad_duration(duration)) {
        // Handle the bad duration scenario
    } else {
        // Optionally, perform some checks or operations on the valid duration
    }

    delete[] str;
}

extern "C" int LLVMFuzzerTestOneInput_62(const uint8_t *Data, size_t Size) {
    fuzz_icaldurationtype_normalize(Data, Size);
    fuzz_icaldurationtype_null_duration();
    fuzz_icaldurationtype_as_ical_string_r(Data, Size);
    fuzz_icaldurationtype_as_ical_string(Data, Size);
    fuzz_icaldurationtype_bad_duration();
    fuzz_icaldurationtype_from_string(Data, Size);

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

        LLVMFuzzerTestOneInput_62(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    