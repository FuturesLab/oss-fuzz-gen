#include <sys/stat.h>
#include <string.h>
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
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Create a string from the input data
    std::string icalStr(reinterpret_cast<const char*>(Data), Size);

    // Use the icalcomponent_new_from_string function
    icalcomponent *component = icalcomponent_new_from_string(icalStr.c_str());

    if (component) {
        // Use the icalcomponent_get_location function
        const char *location = icalcomponent_get_location(component);

        // Use the icalcomponent_isa function
        icalcomponent_kind kind = icalcomponent_isa(component);

        // Use the icalcomponent_get_recurrenceid function
        struct icaltimetype recurrenceId = icalcomponent_get_recurrenceid(component);

        // Loop through different component kinds for icalcomponent_get_first_component
        for (int kindIndex = ICAL_NO_COMPONENT; kindIndex < ICAL_NUM_COMPONENT_TYPES; ++kindIndex) {
            icalcomponent *firstComponent = icalcomponent_get_first_component(component, static_cast<icalcomponent_kind>(kindIndex));
            // Just to simulate usage
            if (firstComponent) {
                const char *comment = icalcomponent_get_comment(firstComponent);
            
                // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_get_comment to icalcomponent_set_duration
                // Ensure dataflow is valid (i.e., non-null)
                if (!firstComponent) {
                	return 0;
                }
                struct icaldurationtype ret_icalcomponent_get_duration_qchvp = icalcomponent_get_duration(firstComponent);
                // Ensure dataflow is valid (i.e., non-null)
                if (!firstComponent) {
                	return 0;
                }
                icalcomponent_set_duration(firstComponent, ret_icalcomponent_get_duration_qchvp);
                // End mutation: Producer.APPEND_MUTATOR
                
}
        }

        // Use the icalcomponent_get_comment function
        const char *comment = icalcomponent_get_comment(component);

        // Free the component
        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalcomponent_free with icalcomponent_normalize
        icalcomponent_normalize(component);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_new_from_string to icalcomponent_get_timezone
    // Ensure dataflow is valid (i.e., non-null)
    if (!component) {
    	return 0;
    }
    char* ret_icalcomponent_as_ical_string_vtbic = icalcomponent_as_ical_string(component);
    if (ret_icalcomponent_as_ical_string_vtbic == NULL){
    	return 0;
    }
    // Ensure dataflow is valid (i.e., non-null)
    if (!component) {
    	return 0;
    }
    // Ensure dataflow is valid (i.e., non-null)
    if (!ret_icalcomponent_as_ical_string_vtbic) {
    	return 0;
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_as_ical_string to icalcomponent_set_location
    // Ensure dataflow is valid (i.e., non-null)
    if (!ret_icalcomponent_as_ical_string_vtbic) {
    	return 0;
    }
    icalcomponent* ret_icalcomponent_new_from_string_ifgbj = icalcomponent_new_from_string(ret_icalcomponent_as_ical_string_vtbic);
    if (ret_icalcomponent_new_from_string_ifgbj == NULL){
    	return 0;
    }
    // Ensure dataflow is valid (i.e., non-null)
    if (!ret_icalcomponent_new_from_string_ifgbj) {
    	return 0;
    }
    // Ensure dataflow is valid (i.e., non-null)
    if (!ret_icalcomponent_as_ical_string_vtbic) {
    	return 0;
    }
    icalcomponent_set_location(ret_icalcomponent_new_from_string_ifgbj, ret_icalcomponent_as_ical_string_vtbic);
    // End mutation: Producer.APPEND_MUTATOR
    
    icaltimezone* ret_icalcomponent_get_timezone_pqykh = icalcomponent_get_timezone(component, ret_icalcomponent_as_ical_string_vtbic);
    if (ret_icalcomponent_get_timezone_pqykh == NULL){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_16(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
