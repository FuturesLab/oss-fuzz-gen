// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icaltimezone_dump_changes at icaltimezone.c:1984:6 in icaltimezone.h
// icaltimezone_free at icaltimezone.c:259:6 in icaltimezone.h
// icaltimezone_get_utc_offset_of_utc_time at icaltimezone.c:999:5 in icaltimezone.h
// icaltimezone_get_utc_offset at icaltimezone.c:834:5 in icaltimezone.h
// icaltimezone_get_utc_timezone at icaltimezone.c:1568:15 in icaltimezone.h
// icaltimezone_copy at icaltimezone.c:225:15 in icaltimezone.h
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
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icaltimezone.h"

extern "C" int LLVMFuzzerTestOneInput_137(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    // Prepare a dummy file
    FILE *fp = fopen("./dummy_file", "w+");
    if (!fp) return 0;

    // Prepare a max_year from input data
    int max_year = *reinterpret_cast<const int*>(Data);
    Data += sizeof(int);
    Size -= sizeof(int);

    // Get the UTC timezone
    icaltimezone *utc_zone = icaltimezone_get_utc_timezone();
    if (!utc_zone) {
        fclose(fp);
        return 0;
    }

    // Copy the UTC timezone
    icaltimezone *zone_copy = icaltimezone_copy(utc_zone);
    if (!zone_copy) {
        fclose(fp);
        return 0;
    }

    // Fuzz icaltimezone_dump_changes
    icaltimezone_dump_changes(zone_copy, max_year, fp);

    // Prepare an icaltimetype for offset calculations
    struct icaltimetype tt;
    tt.year = max_year;  // Use max_year as the year
    tt.zone = utc_zone;

    int is_daylight = 0;

    // Fuzz icaltimezone_get_utc_offset
    icaltimezone_get_utc_offset(zone_copy, &tt, &is_daylight);

    // Fuzz icaltimezone_get_utc_offset_of_utc_time
    icaltimezone_get_utc_offset_of_utc_time(zone_copy, &tt, &is_daylight);

    // Cleanup
    icaltimezone_free(zone_copy, 1);
    fclose(fp);

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

        LLVMFuzzerTestOneInput_137(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    