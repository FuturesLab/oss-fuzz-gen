#include <sys/stat.h>
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
#include <assert.h>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalduration.h"
#include <string.h>
#include <iostream>

extern "C" int LLVMFuzzerTestOneInput_215(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Convert input data to an integer for seconds
    int seconds = static_cast<int>(Data[0]);

    // Test icaldurationtype_from_seconds
    struct icaldurationtype duration = icaldurationtype_from_seconds(seconds);

    // Test icaldurationtype_as_utc_seconds
    int utc_seconds = icaldurationtype_as_utc_seconds(duration);

    // Test icaldurationtype_normalize
    struct icaldurationtype normalized_duration = icaldurationtype_normalize(duration);

    // Test icaldurationtype_null_duration
    struct icaldurationtype null_duration = icaldurationtype_null_duration();
    assert(null_duration.days == 0);
    assert(null_duration.weeks == 0);
    assert(null_duration.hours == 0);
    assert(null_duration.minutes == 0);
    assert(null_duration.seconds == 0);

    // Test icaldurationtype_as_seconds
    int duration_seconds = icaldurationtype_as_seconds(duration);

    // Prepare a string for icaldurationtype_from_string
    char duration_str[Size + 1];
    memcpy(duration_str, Data, Size);
    duration_str[Size] = '\0';

    // Test icaldurationtype_from_string
    struct icaldurationtype from_string_duration = icaldurationtype_from_string(duration_str);

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

    LLVMFuzzerTestOneInput_215(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
