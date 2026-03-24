#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include "/src/libical/src/libical/icalcomponent.h"
}

extern "C" int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a valid icalcomponent
    if (size < 1) {
        return 0;
    }

    // Create a temporary buffer to hold the data
    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL) {
        return 0;
    }

    // Copy the data into the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Create an icalcomponent from the buffer
    icalcomponent *component = icalcomponent_new_from_string(buffer);

    // Ensure the component is not NULL before calling the function-under-test
    if (component != NULL) {
        // Call the function-under-test
        icalcomponent_kind kind = icalcomponent_isa(component);

        // Clean up the component

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalcomponent_free with icalcomponent_normalize

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_isa to icalcomponent_end_component
        bool ret_icalcomponent_check_restrictions_pyfiy = icalcomponent_check_restrictions(component);
        if (ret_icalcomponent_check_restrictions_pyfiy == 0){
        	return 0;
        }


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_check_restrictions to icalcomponent_get_timezone
        char* ret_icalcomponent_as_ical_string_r_hrhjz = icalcomponent_as_ical_string_r(component);
        if (ret_icalcomponent_as_ical_string_r_hrhjz == NULL){
        	return 0;
        }

        icaltimezone* ret_icalcomponent_get_timezone_ezvoa = icalcomponent_get_timezone(component, ret_icalcomponent_as_ical_string_r_hrhjz);
        if (ret_icalcomponent_get_timezone_ezvoa == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        icalcompiter ret_icalcomponent_end_component_xtywb = icalcomponent_end_component(component, kind);

        // End mutation: Producer.APPEND_MUTATOR

        icalcomponent_normalize(component);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


    }

    // Free the temporary buffer
    free(buffer);

    return 0;
}