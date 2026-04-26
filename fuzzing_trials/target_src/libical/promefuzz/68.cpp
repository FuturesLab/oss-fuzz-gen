// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalenum_reqstat_minor at icalenums.c:122:7 in icalenums.h
// icalenum_reqstat_major at icalenums.c:109:7 in icalenums.h
// icalenum_num_to_reqstat at icalenums.c:135:19 in icalenums.h
// icalenum_reqstat_desc at icalenums.c:69:13 in icalenums.h
// icalenum_reqstat_code at icalenums.c:83:7 in icalenums.h
// icalenum_reqstat_code_r at icalenums.c:92:7 in icalenums.h
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
#include <cstdlib>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <icalenums.h>

extern "C" int LLVMFuzzerTestOneInput_68(const uint8_t *Data, size_t Size) {
    if (Size < 2) {
        return 0;
    }

    // Extract a short from the input data for major/minor status
    short major = static_cast<short>(Data[0]);
    short minor = static_cast<short>(Data[1]);

    // Use the first byte as an index into the icalrequeststatus enum
    icalrequeststatus stat = static_cast<icalrequeststatus>(Data[0]);

    // Test icalenum_reqstat_code
    // Do not free the result of icalenum_reqstat_code, as it is managed by libical's memory management
    char *code = icalenum_reqstat_code(stat);

    // Test icalenum_reqstat_minor
    short minor_code = icalenum_reqstat_minor(stat);

    // Test icalenum_reqstat_desc
    const char *desc = icalenum_reqstat_desc(stat);

    // Test icalenum_reqstat_major
    short major_code = icalenum_reqstat_major(stat);

    // Test icalenum_num_to_reqstat
    icalrequeststatus reqstat = icalenum_num_to_reqstat(major, minor);

    // Test icalenum_reqstat_code_r
    char *code_r = icalenum_reqstat_code_r(stat);
    if (code_r) {
        free(code_r);
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

        if(size < 1 + 1)
            exit(0);

        data = (uint8_t *)malloc((size_t)size);
        if(data == NULL)
            exit(0);

        if(fread(data, (size_t)size, 1, f) != 1)
            exit(0);

        LLVMFuzzerTestOneInput_68(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    