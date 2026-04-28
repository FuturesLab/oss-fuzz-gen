// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalperiodtype_from_string at icalperiod.c:20:23 in icalperiod.h
// icalperiodtype_as_ical_string_r at icalperiod.c:91:7 in icalperiod.h
// icalperiodtype_as_ical_string at icalperiod.c:82:13 in icalperiod.h
// icalperiodtype_null_period at icalperiod.c:121:23 in icalperiod.h
// icalperiodtype_is_valid_period at icalperiod.c:142:6 in icalperiod.h
// icalperiodtype_is_null_period at icalperiod.c:132:6 in icalperiod.h
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
#include "icalperiod.h"
}

#include <cstdint>
#include <cstdlib>
#include <cstring>

static void fuzz_icalperiodtype_functions(const char *str) {
    // Convert string to icalperiodtype
    struct icalperiodtype period = icalperiodtype_from_string(str);

    // Check if the period is null
    bool is_null = icalperiodtype_is_null_period(period);

    // Check if the period is valid
    bool is_valid = icalperiodtype_is_valid_period(period);

    // Convert icalperiodtype to iCal-formatted string (caller owns the result)
    char *ical_string_r = icalperiodtype_as_ical_string_r(period);
    if (ical_string_r) {
        // Free the dynamically allocated string
        icalmemory_free_buffer(ical_string_r);
    }

    // Convert icalperiodtype to iCal-formatted string (libical owns the result)
    const char *ical_string = icalperiodtype_as_ical_string(period);

    // Create a null period and check its properties
    struct icalperiodtype null_period = icalperiodtype_null_period();
    bool is_null_period = icalperiodtype_is_null_period(null_period);
    bool is_valid_null_period = icalperiodtype_is_valid_period(null_period);

    // Use the results to prevent compiler optimizations
    volatile bool dummy = is_null || is_valid || is_null_period || is_valid_null_period || (ical_string != nullptr);
}

extern "C" int LLVMFuzzerTestOneInput_80(const uint8_t *Data, size_t Size) {
    // Ensure null-termination of input data
    char *input = static_cast<char *>(malloc(Size + 1));
    if (!input) return 0;
    memcpy(input, Data, Size);
    input[Size] = '\0';

    // Fuzz the icalperiodtype functions
    fuzz_icalperiodtype_functions(input);

    free(input);
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

        LLVMFuzzerTestOneInput_80(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    