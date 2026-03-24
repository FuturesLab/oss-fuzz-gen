#include "libical/ical.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
    // Ensure the input size is reasonable to prevent excessive memory allocation
    if (size == 0 || size > 1024) {
        return 0;
    }

    // Allocate memory for the input data and ensure it's null-terminated
    char *ical_data = (char *)malloc(size + 1);
    if (ical_data == NULL) {
        return 0;
    }
    memcpy(ical_data, data, size);
    ical_data[size] = '\0';

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(ical_data);
    free(ical_data);

    if (component == NULL) {
        return 0;
    }

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalcomponent_get_recurrenceid with icalcomponent_get_dtstamp

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalcomponent_get_dtstamp with icalcomponent_get_due
    struct icaltimetype recurrence_id = icalcomponent_get_due(component);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_free to icalcomponent_set_description

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_get_due to icalcomponent_set_uid

    icalcomponent_set_uid(component, NULL);

    // End mutation: Producer.APPEND_MUTATOR

    char* ret_icalcomponent_as_ical_string_mbaee = icalcomponent_as_ical_string(component);
    if (ret_icalcomponent_as_ical_string_mbaee == NULL){
    	return 0;
    }

    icalcomponent_set_description(component, ret_icalcomponent_as_ical_string_mbaee);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalcomponent_free with icalcomponent_normalize
    icalcomponent_normalize(component);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    return 0;
}