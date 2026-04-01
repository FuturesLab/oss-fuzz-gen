#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include "/src/libical/src/libical/icalcomponent.h"
}

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
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
        icalcomponent_normalize(component);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


    }

    // Free the temporary buffer

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_new_from_string to icalcomponent_isa_component


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_new_from_string to icalcomponent_set_description
    char* ret_icalcomponent_get_component_name_r_nwdnu = icalcomponent_get_component_name_r(component);
    if (ret_icalcomponent_get_component_name_r_nwdnu == NULL){
    	return 0;
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_get_component_name_r to icalcomponent_get_timezone
    icalcomponent* ret_icalcomponent_new_xdaylight_lednh = icalcomponent_new_xdaylight();
    if (ret_icalcomponent_new_xdaylight_lednh == NULL){
    	return 0;
    }

    icaltimezone* ret_icalcomponent_get_timezone_xjpzo = icalcomponent_get_timezone(ret_icalcomponent_new_xdaylight_lednh, ret_icalcomponent_get_component_name_r_nwdnu);
    if (ret_icalcomponent_get_timezone_xjpzo == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    icalcomponent_set_description(component, ret_icalcomponent_get_component_name_r_nwdnu);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of icalcomponent_isa_component
    bool ret_icalcomponent_isa_component_wqudw = icalcomponent_isa_component((const void *)data);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_icalcomponent_isa_component_wqudw == 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_normalize to icalcomponent_get_duration

        struct icaldurationtype ret_icalcomponent_get_duration_jpsxl = icalcomponent_get_duration(component);

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_normalize to icalcomponent_set_parent
        icalcomponent* ret_icalproperty_get_parent_vfosa = icalproperty_get_parent(NULL);
        if (ret_icalproperty_get_parent_vfosa == NULL){
        	return 0;
        }

        icalcomponent_set_parent(ret_icalproperty_get_parent_vfosa, component);

        // End mutation: Producer.APPEND_MUTATOR

    free(buffer);

    return 0;
}