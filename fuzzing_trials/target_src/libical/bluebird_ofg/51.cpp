#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include "/src/libical/src/libical/icalcomponent.h"
}

extern "C" int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
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

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_isa to icalcomponent_get_next_component

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalcomponent_new_vtimezone with icalcomponent_new_xavailable
        icalcomponent* ret_icalcomponent_new_vtimezone_jgsyw = icalcomponent_new_xavailable();
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        if (ret_icalcomponent_new_vtimezone_jgsyw == NULL){
        	return 0;
        }

        icalcomponent* ret_icalcomponent_get_next_component_jzxxz = icalcomponent_get_next_component(ret_icalcomponent_new_vtimezone_jgsyw, kind);
        if (ret_icalcomponent_get_next_component_jzxxz == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        icalcomponent_free(component);
    }

    // Free the temporary buffer
    free(buffer);

    return 0;
}