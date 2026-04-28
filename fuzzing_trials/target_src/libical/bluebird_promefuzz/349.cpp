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
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icaltimezone.h"

extern "C" int LLVMFuzzerTestOneInput_349(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Convert input data to a null-terminated string
    std::string input(reinterpret_cast<const char*>(Data), Size);

    // Test icaltimezone_get_builtin_timezone
    icaltimezone *zone = icaltimezone_get_builtin_timezone(input.c_str());
    if (zone) {
        // Test icaltimezone_get_display_name
        const char *display_name = icaltimezone_get_display_name(zone);
        if (display_name) {
            std::cout << "Display Name: " << display_name << std::endl;
        }

        // Test icaltimezone_get_tznames
        const char *tz_names = icaltimezone_get_tznames(zone);
        if (tz_names) {
            std::cout << "TZ Names: " << tz_names << std::endl;
        }

        // Test icaltimezone_get_location
        const char *location = icaltimezone_get_location(zone);
        if (location) {
            std::cout << "Location: " << location << std::endl;
        }

        // Test icaltimezone_get_tzid
        const char *tzid = icaltimezone_get_tzid(zone);
        if (tzid) {
            std::cout << "TZID: " << tzid << std::endl;
        }
    }

    // Test icaltimezone_get_builtin_timezone_from_tzid
    zone = icaltimezone_get_builtin_timezone_from_tzid(input.c_str());
    if (zone) {
        // Test icaltimezone_get_display_name
        const char *display_name = icaltimezone_get_display_name(zone);
        if (display_name) {
            std::cout << "Display Name from TZID: " << display_name << std::endl;
        }

        // Test icaltimezone_get_tznames
        const char *tz_names = icaltimezone_get_tznames(zone);
        if (tz_names) {
            std::cout << "TZ Names from TZID: " << tz_names << std::endl;
        }

        // Test icaltimezone_get_location
        const char *location = icaltimezone_get_location(zone);
        if (location) {
            std::cout << "Location from TZID: " << location << std::endl;
        }

        // Test icaltimezone_get_tzid
        const char *tzid = icaltimezone_get_tzid(zone);
        if (tzid) {
            std::cout << "TZID from TZID: " << tzid << std::endl;
        }
    }

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

    LLVMFuzzerTestOneInput_349(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
