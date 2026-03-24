#include "libical/ical.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    // Check if the size is sufficient to extract a property kind
    if (size < sizeof(icalproperty_kind) + 1) { // Ensure there's at least one character for the string
        return 0;
    }

    // Ensure the data is null-terminated to prevent buffer overflows in string functions
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0;
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Create an icalcomponent from the input data
    icalcomponent *component = icalcomponent_new_from_string(null_terminated_data);
    if (component == NULL) {
        free(null_terminated_data);
        return 0;
    }

    // Extract icalproperty_kind from the input data

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_new_from_string to icalcomponent_set_due
    struct icaltimetype ret_icalcomponent_get_dtend_knqwe = icalcomponent_get_dtend(component);

    icalcomponent_set_due(component, ret_icalcomponent_get_dtend_knqwe);

    // End mutation: Producer.APPEND_MUTATOR

    icalproperty_kind kind = static_cast<icalproperty_kind>(data[0]);

    // Call the function under test
    icalproperty *property = icalcomponent_get_first_property(component, kind);

    // Clean up
    if (property != NULL) {
        icalproperty_free(property);
    }
    icalcomponent_free(component);
    free(null_terminated_data);

    return 0;
}