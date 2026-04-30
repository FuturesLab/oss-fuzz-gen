// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// ical_set_unknown_token_handling_setting at icaltypes.c:197:6 in icaltypes.h
// ical_get_unknown_token_handling_setting at icaltypes.c:180:29 in icaltypes.h
// ical_set_invalid_rrule_handling_setting at icalrecur.c:4193:6 in icalrecur.h
// ical_get_invalid_rrule_handling_setting at icalrecur.c:4176:29 in icalrecur.h
// icalrecur_expand_recurrence at icalrecur.c:4140:6 in icalrecur.h
// icalerror_get_errors_are_fatal at icalerror.c:105:6 in icalerror.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <fstream>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <icaltypes.h>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <icalerror.h>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <icalrecur.h>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_120(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Fuzz ical_set_invalid_rrule_handling_setting
    ical_invalid_rrule_handling rruleHandlingSetting = static_cast<ical_invalid_rrule_handling>(Data[0] % 2);
    ical_set_invalid_rrule_handling_setting(rruleHandlingSetting);

    // Fuzz ical_get_invalid_rrule_handling_setting
    ical_invalid_rrule_handling currentRruleHandlingSetting = ical_get_invalid_rrule_handling_setting();
    (void)currentRruleHandlingSetting; // Silence unused variable warning

    // Fuzz ical_set_unknown_token_handling_setting
    if (Size < 2) return 0;
    ical_unknown_token_handling tokenHandlingSetting = static_cast<ical_unknown_token_handling>(Data[1] % 3 + 1);
    ical_set_unknown_token_handling_setting(tokenHandlingSetting);

    // Fuzz ical_get_unknown_token_handling_setting
    ical_unknown_token_handling currentTokenHandlingSetting = ical_get_unknown_token_handling_setting();
    (void)currentTokenHandlingSetting; // Silence unused variable warning

    // Fuzz icalerror_get_errors_are_fatal
    bool errorsAreFatal = icalerror_get_errors_are_fatal();
    (void)errorsAreFatal; // Silence unused variable warning

    // Fuzz icalrecur_expand_recurrence
    if (Size < 3) return 0;
    const char *rrule = reinterpret_cast<const char*>(Data + 2);
    size_t rruleSize = Size - 2;
    char rruleBuffer[rruleSize + 1];
    memcpy(rruleBuffer, rrule, rruleSize);
    rruleBuffer[rruleSize] = '\0';

    icaltime_t start = 0; // Placeholder start time
    int count = 10; // Arbitrary count for occurrences
    icaltime_t occurrences[10]; // Array to store occurrences

    bool expandResult = icalrecur_expand_recurrence(rruleBuffer, start, count, occurrences);
    (void)expandResult; // Silence unused variable warning

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

        LLVMFuzzerTestOneInput_120(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    