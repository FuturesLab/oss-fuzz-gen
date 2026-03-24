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

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
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

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalcomponent_set_uid with icalcomponent_set_summary
        icalcomponent_set_summary(comp, "Sample UID");
        // End mutation: Producer.REPLACE_FUNC_MUTATOR



        // Set summary
        icalcomponent_set_summary(comp, "Sample Summary");

        // Convert back to string

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_set_summary to icalcomponent_set_comment

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_set_summary to icalcomponent_set_dtstamp
        struct icaltimetype ret_icalcomponent_get_due_nnxar = icalcomponent_get_due(comp);

        icalcomponent_set_dtstamp(comp, ret_icalcomponent_get_due_nnxar);

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalcomponent_as_ical_string_r with icalcomponent_as_ical_string
        char* ret_icalcomponent_as_ical_string_r_esthn = icalcomponent_as_ical_string(comp);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        if (ret_icalcomponent_as_ical_string_r_esthn == NULL){
        	return 0;
        }


        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalcomponent_set_comment with icalcomponent_set_summary
        icalcomponent_set_summary(comp, ret_icalcomponent_as_ical_string_r_esthn);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR



        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_set_comment to icalcomponent_normalize


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_set_summary to icalcomponent_get_span

        struct icaltime_span ret_icalcomponent_get_span_yefbo = icalcomponent_get_span(comp);

        // End mutation: Producer.APPEND_MUTATOR

        icalcomponent_normalize(comp);

        // End mutation: Producer.APPEND_MUTATOR

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