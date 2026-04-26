// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icaldurationtype_is_bad_duration at icalduration.c:287:6 in icalduration.h
// icaldurationtype_is_null_duration at icalduration.c:265:6 in icalduration.h
// icaldurationtype_bad_duration at icalduration.c:278:25 in icalduration.h
// icaldurationtype_null_duration at icalduration.c:256:25 in icalduration.h
// icaldurationtype_normalize at icalduration.c:364:25 in icalduration.h
// icaldurationtype_from_seconds at icalduration.c:23:25 in icalduration.h
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
#include <cstring>
#include <cassert>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalduration.h"

extern "C" int LLVMFuzzerTestOneInput_130(const uint8_t *Data, size_t Size) {
    // Prepare a buffer for reading an integer from the input data
    if (Size < sizeof(int)) {
        return 0; // Not enough data for an integer
    }

    int seconds;
    std::memcpy(&seconds, Data, sizeof(int));

    // Test icaldurationtype_from_seconds
    struct icaldurationtype duration_from_seconds = icaldurationtype_from_seconds(seconds);

    // Test icaldurationtype_normalize
    struct icaldurationtype normalized_duration = icaldurationtype_normalize(duration_from_seconds);

    // Test icaldurationtype_is_bad_duration
    bool is_bad = icaldurationtype_is_bad_duration(duration_from_seconds);

    // Test icaldurationtype_null_duration
    struct icaldurationtype null_duration = icaldurationtype_null_duration();

    // Test icaldurationtype_is_null_duration
    bool is_null = icaldurationtype_is_null_duration(null_duration);

    // Test icaldurationtype_bad_duration
    struct icaldurationtype bad_duration = icaldurationtype_bad_duration();

    // Verify the behavior of the functions with assertions
    assert((seconds < 0 && duration_from_seconds.is_neg == 1) || (seconds >= 0 && duration_from_seconds.is_neg == 0));
    assert(!icaldurationtype_is_bad_duration(null_duration));
    assert(icaldurationtype_is_null_duration(null_duration));
    assert(icaldurationtype_is_bad_duration(bad_duration));

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

        LLVMFuzzerTestOneInput_130(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    