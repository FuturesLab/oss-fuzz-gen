#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include "/src/libical/src/libical/icalcomponent.h"
}

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
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

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_isa to icalcomponent_count_components
        struct icaltimetype ret_icalcomponent_get_dtend_lvyzk = icalcomponent_get_dtend(component);

        int ret_icalcomponent_count_components_jwjaa = icalcomponent_count_components(component, kind);
        if (ret_icalcomponent_count_components_jwjaa < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_count_components to icalcomponent_set_recurrenceid
        struct icaltimetype ret_icalcomponent_get_dtstart_gsfvx = icalcomponent_get_dtstart(component);

        icalcomponent_set_recurrenceid(component, ret_icalcomponent_get_dtstart_gsfvx);

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalcomponent_free with icalcomponent_normalize

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_set_recurrenceid to icalcomponent_remove_component
        int ret_icalcomponent_get_sequence_aacpg = icalcomponent_get_sequence(component);
        if (ret_icalcomponent_get_sequence_aacpg < 0){
        	return 0;
        }

        icalcomponent_remove_component(component, component);

        // End mutation: Producer.APPEND_MUTATOR

        icalcomponent_normalize(component);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


    }

    // Free the temporary buffer

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_new_from_string to icalcomponent_set_parent
    icalcomponent* ret_icalcomponent_get_inner_mvenb = icalcomponent_get_inner(component);
    if (ret_icalcomponent_get_inner_mvenb == NULL){
    	return 0;
    }

    icalcomponent_set_parent(component, component);

    // End mutation: Producer.APPEND_MUTATOR

    free(buffer);

    return 0;
}