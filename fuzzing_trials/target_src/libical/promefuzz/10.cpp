// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_new_from_string at icalcomponent.c:124:16 in icalcomponent.h
// icalcomponent_as_ical_string_r at icalcomponent.c:226:7 in icalcomponent.h
// icalcomponent_set_comment at icalcomponent.c:1769:6 in icalcomponent.h
// icalcomponent_set_uid at icalcomponent.c:1804:6 in icalcomponent.h
// icalcomponent_set_summary at icalcomponent.c:1734:6 in icalcomponent.h
// icalcomponent_set_description at icalcomponent.c:1885:6 in icalcomponent.h
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
#include <cstring>
#include <cstdlib>
#include "ical.h"

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Convert input data to a null-terminated string
    char *inputData = (char *)malloc(Size + 1);
    if (!inputData) return 0;
    memcpy(inputData, Data, Size);
    inputData[Size] = '\0';

    // Create icalcomponent from string
    icalcomponent *comp = icalcomponent_new_from_string(inputData);
    if (comp) {
        // Set description
        icalcomponent_set_description(comp, "Sample Description");

        // Set comment
        icalcomponent_set_comment(comp, "Sample Comment");

        // Set UID
        icalcomponent_set_uid(comp, "Sample UID");

        // Set summary
        icalcomponent_set_summary(comp, "Sample Summary");

        // Convert back to string
        char *icalString = icalcomponent_as_ical_string_r(comp);
        if (icalString) {
            // Normally, we would do something with the string, but for fuzzing, just free it
            free(icalString);
        }

        // Free the icalcomponent
        icalcomponent_free(comp);
    }

    free(inputData);
    return 0;
}