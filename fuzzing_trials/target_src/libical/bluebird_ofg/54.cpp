#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include "/src/libical/src/libical/icalcomponent.h"
}

extern "C" int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
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

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_isa to icalcomponent_begin_component
        icalcomponent* ret_icalcomponent_new_vquery_qloqk = icalcomponent_new_vquery();
        if (ret_icalcomponent_new_vquery_qloqk == NULL){
        	return 0;
        }

        icalcompiter ret_icalcomponent_begin_component_yhjvg = icalcomponent_begin_component(ret_icalcomponent_new_vquery_qloqk, kind);

        // End mutation: Producer.APPEND_MUTATOR

        icalcomponent_normalize(component);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


    }

    // Free the temporary buffer

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_new_from_string to icalcomponent_get_method

    icalproperty_method ret_icalcomponent_get_method_dhicx = icalcomponent_get_method(component);

    // End mutation: Producer.APPEND_MUTATOR

    free(buffer);

    return 0;
}