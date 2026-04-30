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
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_45(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Ensure null-terminated string for icalcomponent_new_from_string
    char *icalStr = static_cast<char*>(malloc(Size + 1));
    if (!icalStr) {
        return 0;
    }
    memcpy(icalStr, Data, Size);
    icalStr[Size] = '\0';

    // Create icalcomponent from string
    icalcomponent *comp = icalcomponent_new_from_string(icalStr);
    free(icalStr);

    if (comp) {
        // Test icalcomponent_isa_component
        icalcomponent_isa_component(comp);

        // Setup a dummy icaltimetype for testing
        struct icaltimetype dtstart = {0};
        struct icaltimetype recurtime = {0};

        // Test icalproperty_recurrence_is_excluded
        icalproperty_recurrence_is_excluded(comp, &dtstart, &recurtime);

        // Test icalcomponent_set_description
        icalcomponent_set_description(comp, "Sample Description");

        // Test icalcomponent_kind_is_valid
        icalcomponent_kind kind = icalcomponent_isa(comp);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_isa to icalcomponent_get_next_component
        // Ensure dataflow is valid (i.e., non-null)
        if (!comp) {
        	return 0;
        }
        struct icaldurationtype ret_icalcomponent_get_duration_snzqz = icalcomponent_get_duration(comp);
        // Ensure dataflow is valid (i.e., non-null)
        if (!comp) {
        	return 0;
        }

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_get_duration to icalcomponent_remove_property
        // Ensure dataflow is valid (i.e., non-null)
        if (!comp) {
        	return 0;
        }
        icalproperty* ret_icalcomponent_get_current_property_aizyf = icalcomponent_get_current_property(comp);
        if (ret_icalcomponent_get_current_property_aizyf == NULL){
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!comp) {
        	return 0;
        }
        // Ensure dataflow is valid (i.e., non-null)
        if (!ret_icalcomponent_get_current_property_aizyf) {
        	return 0;
        }
        icalcomponent_remove_property(comp, ret_icalcomponent_get_current_property_aizyf);
        // End mutation: Producer.APPEND_MUTATOR
        
        icalcomponent* ret_icalcomponent_get_next_component_coxgh = icalcomponent_get_next_component(comp, kind);
        if (ret_icalcomponent_get_next_component_coxgh == NULL){
        	return 0;
        }
        // End mutation: Producer.APPEND_MUTATOR
        
        icalcomponent_kind_is_valid(kind);

        // Test icalcomponent_is_valid
        icalcomponent_is_valid(comp);

        // Cleanup the component
        icalcomponent_free(comp);
    }

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

    LLVMFuzzerTestOneInput_45(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
