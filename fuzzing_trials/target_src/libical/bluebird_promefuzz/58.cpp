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
#include "libical/ical.h"

extern "C" int LLVMFuzzerTestOneInput_58(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Convert input data to a null-terminated string
    char *inputData = (char *)malloc(Size + 1);
    if (!inputData) {
        return 0;
    }
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

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_set_comment to icalcomponent_set_dtstamp
        struct icaltimetype ret_icalcomponent_get_dtend_ejlmo = icalcomponent_get_dtend(comp);

        icalcomponent_set_dtstamp(comp, ret_icalcomponent_get_dtend_ejlmo);

        // End mutation: Producer.APPEND_MUTATOR

        icalcomponent_set_uid(comp, "Sample UID");

        // Set summary

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of icalcomponent_set_summary
        const char qcjnbuxb[1024] = "tdeyf";
        icalcomponent_set_summary(comp, qcjnbuxb);
        // End mutation: Producer.REPLACE_ARG_MUTATOR



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