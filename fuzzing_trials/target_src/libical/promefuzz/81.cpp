// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icaltriggertype_is_bad_trigger at icaltypes.c:34:6 in icaltypes.h
// icaltriggertype_is_null_trigger at icaltypes.c:25:6 in icaltypes.h
// icaldurationtype_is_null_duration at icalduration.c:265:6 in icalduration.h
// icaltriggertype_from_seconds at icaltypes.c:43:24 in icaltypes.h
// icaltriggertype_from_string at icaltypes.c:53:24 in icaltypes.h
// icaldurationtype_from_string at icalduration.c:38:25 in icalduration.h
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
#include <cstddef>
#include <cassert>
#include <cstring>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icaltypes.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalduration.h"

extern "C" int LLVMFuzzerTestOneInput_81(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Convert input data to a string for string-based functions
    char *inputStr = new char[Size + 1];
    memcpy(inputStr, Data, Size);
    inputStr[Size] = '\0';

    // 1. Test icaltriggertype_from_string
    struct icaltriggertype triggerFromString = icaltriggertype_from_string(inputStr);

    // 2. Test icaltriggertype_is_null_trigger
    bool isNullTrigger = icaltriggertype_is_null_trigger(triggerFromString);

    // 3. Test icaldurationtype_from_string
    struct icaldurationtype durationFromString = icaldurationtype_from_string(inputStr);

    // 4. Test icaldurationtype_is_null_duration
    bool isNullDuration = icaldurationtype_is_null_duration(durationFromString);

    // 5. Test icaltriggertype_from_seconds
    int seconds = static_cast<int>(Data[0]); // Use first byte as a simple integer
    struct icaltriggertype triggerFromSeconds = icaltriggertype_from_seconds(seconds);

    // 6. Test icaltriggertype_is_bad_trigger
    bool isBadTrigger = icaltriggertype_is_bad_trigger(triggerFromString);

    // Cleanup
    delete[] inputStr;

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

        LLVMFuzzerTestOneInput_81(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    