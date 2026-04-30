// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icaltimezone_free_builtin_timezones at icaltimezone.c:1375:6 in icaltimezone.h
// icaltimezone_free at icaltimezone.c:259:6 in icaltimezone.h
// icaltimezone_get_builtin_timezone_from_offset at icaltimezone.c:1466:15 in icaltimezone.h
// icaltimezone_get_builtin_timezone at icaltimezone.c:1383:15 in icaltimezone.h
// icaltimezone_get_tzid at icaltimezone.c:1210:13 in icaltimezone.h
// icaltimezone_set_zone_directory at icaltimezone.c:2258:6 in icaltimezone.h
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
#include "icaltimezone.h"
}

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fstream>

static void fuzz_icaltimezone_set_zone_directory(const uint8_t *Data, size_t Size) {
    char *path = new char[Size + 1];
    memcpy(path, Data, Size);
    path[Size] = '\0';
    icaltimezone_set_zone_directory(path);
    delete[] path;
}

static void fuzz_icaltimezone_get_builtin_timezone(const uint8_t *Data, size_t Size) {
    char *location = new char[Size + 1];
    memcpy(location, Data, Size);
    location[Size] = '\0';
    icaltimezone *timezone = icaltimezone_get_builtin_timezone(location);
    if (timezone) {
        const char *tzid = icaltimezone_get_tzid(timezone);
        if (tzid) {
            // Do something with tzid if needed
        }
        icaltimezone_free(timezone, 0);
    }
    delete[] location;
}

static void fuzz_icaltimezone_get_builtin_timezone_from_offset(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int offset;
    memcpy(&offset, Data, sizeof(int));
    char *tzname = new char[Size - sizeof(int) + 1];
    memcpy(tzname, Data + sizeof(int), Size - sizeof(int));
    tzname[Size - sizeof(int)] = '\0';
    icaltimezone *timezone = icaltimezone_get_builtin_timezone_from_offset(offset, tzname);
    if (timezone) {
        const char *tzid = icaltimezone_get_tzid(timezone);
        if (tzid) {
            // Do something with tzid if needed
        }
        icaltimezone_free(timezone, 0);
    }
    delete[] tzname;
}

extern "C" int LLVMFuzzerTestOneInput_83(const uint8_t *Data, size_t Size) {
    fuzz_icaltimezone_set_zone_directory(Data, Size);
    fuzz_icaltimezone_get_builtin_timezone(Data, Size);
    fuzz_icaltimezone_get_builtin_timezone_from_offset(Data, Size);

    icaltimezone_free_builtin_timezones();

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

        LLVMFuzzerTestOneInput_83(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    