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

extern "C" int LLVMFuzzerTestOneInput_65(const uint8_t *Data, size_t Size) {
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
        icalcomponent_set_uid(comp, "Sample UID");

        // Set summary
        icalcomponent_set_summary(comp, "Sample Summary");

        // Convert back to string

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_set_summary to icalcomponent_get_first_real_component

        icalcomponent* ret_icalcomponent_get_first_real_component_pkfet = icalcomponent_get_first_real_component(comp);
        if (ret_icalcomponent_get_first_real_component_pkfet == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of icalcomponent_as_ical_string_r
        char *icalString = icalcomponent_as_ical_string_r(ret_icalcomponent_get_first_real_component_pkfet);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


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