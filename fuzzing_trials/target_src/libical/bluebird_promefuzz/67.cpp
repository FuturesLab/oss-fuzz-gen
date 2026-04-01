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

extern "C" int LLVMFuzzerTestOneInput_67(const uint8_t *Data, size_t Size) {
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

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalcomponent_get_dtstamp with icalcomponent_get_due
        struct icaltimetype ret_icalcomponent_get_dtstamp_ordtj = icalcomponent_get_due(comp);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR



        icalcomponent_set_dtstamp(comp, ret_icalcomponent_get_dtstamp_ordtj);

        // End mutation: Producer.APPEND_MUTATOR

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

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalcomponent_free with icalcomponent_normalize
        icalcomponent_normalize(comp);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_new_from_string to icalcomponent_add_property
    icalproperty* ret_icalpropiter_next_ljwaj = icalpropiter_next(NULL);
    if (ret_icalpropiter_next_ljwaj == NULL){
    	return 0;
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalpropiter_next to icalproperty_get_parent

    icalcomponent* ret_icalproperty_get_parent_ucqfm = icalproperty_get_parent(ret_icalpropiter_next_ljwaj);
    if (ret_icalproperty_get_parent_ucqfm == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    icalcomponent_add_property(comp, ret_icalpropiter_next_ljwaj);

    // End mutation: Producer.APPEND_MUTATOR

    free(inputData);
    return 0;
}