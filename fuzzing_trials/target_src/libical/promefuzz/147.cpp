// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icaltimezone_free_zone_directory at icaltimezone.c:2273:6 in icaltimezone.h
// icaltimezone_get_system_zone_directory at icaltimezone.c:2240:13 in icaltimezone.h
// icaltimezone_set_system_zone_directory at icaltimezone.c:2205:6 in icaltimezone.h
// icaltimezone_get_zone_directory at icaltimezone.c:2249:13 in icaltimezone.h
// icaltimezone_set_zone_directory at icaltimezone.c:2258:6 in icaltimezone.h
// icaltimezone_get_display_name at icaltimezone.c:1309:13 in icaltimezone.h
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

static void fuzz_icaltimezone_set_zone_directory(const uint8_t *Data, size_t Size) {
    char *path = static_cast<char *>(malloc(Size + 1));
    if (path == nullptr) return;
    memcpy(path, Data, Size);
    path[Size] = '\0';
    icaltimezone_set_zone_directory(path);
    free(path);
}

static void fuzz_icaltimezone_set_system_zone_directory(const uint8_t *Data, size_t Size) {
    char *zonepath = static_cast<char *>(malloc(Size + 1));
    if (zonepath == nullptr) return;
    memcpy(zonepath, Data, Size);
    zonepath[Size] = '\0';
    icaltimezone_set_system_zone_directory(zonepath);
    free(zonepath);
}

static void fuzz_icaltimezone_get_display_name() {
    // As we don't have constructor methods for icaltimezone, we simulate with nullptr
    icaltimezone *zone = nullptr;
    const char *name = icaltimezone_get_display_name(zone);
    (void)name; // Avoid unused variable warning
}

static void fuzz_icaltimezone_get_system_zone_directory() {
    const char *system_zone_dir = icaltimezone_get_system_zone_directory();
    (void)system_zone_dir; // Avoid unused variable warning
}

static void fuzz_icaltimezone_get_zone_directory() {
    const char *zone_dir = icaltimezone_get_zone_directory();
    (void)zone_dir; // Avoid unused variable warning
}

static void fuzz_icaltimezone_free_zone_directory() {
    icaltimezone_free_zone_directory();
}

extern "C" int LLVMFuzzerTestOneInput_147(const uint8_t *Data, size_t Size) {
    fuzz_icaltimezone_set_zone_directory(Data, Size);
    fuzz_icaltimezone_set_system_zone_directory(Data, Size);
    fuzz_icaltimezone_get_display_name();
    fuzz_icaltimezone_get_system_zone_directory();
    fuzz_icaltimezone_get_zone_directory();
    fuzz_icaltimezone_free_zone_directory();
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

        LLVMFuzzerTestOneInput_147(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    