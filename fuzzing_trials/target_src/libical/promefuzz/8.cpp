// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icaltimezone_get_latitude at icaltimezone.c:1246:8 in icaltimezone.h
// icaltimezone_get_longitude at icaltimezone.c:1258:8 in icaltimezone.h
// icaltimezone_copy at icaltimezone.c:225:15 in icaltimezone.h
// icaltimezone_new at icaltimezone.c:210:15 in icaltimezone.h
// icaltimezone_get_builtin_timezone at icaltimezone.c:1383:15 in icaltimezone.h
// icaltimezone_get_builtin_timezone_from_tzid at icaltimezone.c:1499:15 in icaltimezone.h
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
#include <fstream>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icaltimezone.h"

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Prepare a null-terminated string from the input data
    char *inputString = (char *)malloc(Size + 1);
    if (!inputString) return 0;
    memcpy(inputString, Data, Size);
    inputString[Size] = '\0';

    // Test icaltimezone_get_builtin_timezone
    icaltimezone *builtinTimezone = icaltimezone_get_builtin_timezone(inputString);
    if (builtinTimezone) {
        // Test icaltimezone_copy
        icaltimezone *copiedTimezone = icaltimezone_copy(builtinTimezone);
        if (copiedTimezone) {
            // Test icaltimezone_get_latitude
            double latitude = icaltimezone_get_latitude(copiedTimezone);
            (void)latitude; // Suppress unused variable warning

            // Test icaltimezone_get_longitude
            double longitude = icaltimezone_get_longitude(copiedTimezone);
            (void)longitude; // Suppress unused variable warning

            // Free the copied timezone
            icaltimezone_free(copiedTimezone, 1);
        }
    }

    // Test icaltimezone_new
    icaltimezone *newTimezone = icaltimezone_new();
    if (newTimezone) {
        // Test icaltimezone_get_latitude
        double latitude = icaltimezone_get_latitude(newTimezone);
        (void)latitude; // Suppress unused variable warning

        // Test icaltimezone_get_longitude
        double longitude = icaltimezone_get_longitude(newTimezone);
        (void)longitude; // Suppress unused variable warning

        // Free the new timezone
        icaltimezone_free(newTimezone, 1);
    }

    // Test icaltimezone_get_builtin_timezone_from_tzid
    icaltimezone *builtinTimezoneFromTzid = icaltimezone_get_builtin_timezone_from_tzid(inputString);
    if (builtinTimezoneFromTzid) {
        // Test icaltimezone_get_latitude
        double latitude = icaltimezone_get_latitude(builtinTimezoneFromTzid);
        (void)latitude; // Suppress unused variable warning

        // Test icaltimezone_get_longitude
        double longitude = icaltimezone_get_longitude(builtinTimezoneFromTzid);
        (void)longitude; // Suppress unused variable warning
    }

    // Clean up
    free(inputString);
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

        LLVMFuzzerTestOneInput_8(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    