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
#include <cstdlib>
#include <cstring>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    if (Size < 2) {
        return 0;
    }

    // Convert the first byte to an icalcomponent_kind
    icalcomponent_kind componentKind = static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES);

    // Convert the second byte to an icalproperty_kind
    icalproperty_kind propertyKind = static_cast<icalproperty_kind>(Data[1] % ICAL_NO_PROPERTY);

    // Create a new component
    icalcomponent *component = icalcomponent_new(componentKind);
    if (!component) {
        return 0;
    }

    // Create a new property

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_new to icalcomponent_set_recurrenceid
    // Ensure dataflow is valid (i.e., non-null)
    if (!component) {
    	return 0;
    }
    struct icaltimetype ret_icalcomponent_get_recurrenceid_eprli = icalcomponent_get_recurrenceid(component);
    // Ensure dataflow is valid (i.e., non-null)
    if (!component) {
    	return 0;
    }
    icalcomponent_set_recurrenceid(component, ret_icalcomponent_get_recurrenceid_eprli);
    // End mutation: Producer.APPEND_MUTATOR
    
    icalproperty *property = icalproperty_new(propertyKind);
    if (!property) {
        icalcomponent_free(component);
        return 0;
    }

    // Test icalcomponent_add_property
    icalcomponent_add_property(component, property);

    // Test icalcomponent_get_first_property
    icalproperty *firstProperty = icalcomponent_get_first_property(component, propertyKind);

    // Test icalcomponent_get_next_property
    icalproperty *nextProperty = icalcomponent_get_next_property(component, propertyKind);

    // Test icalcomponent_begin_property

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_get_next_property to icalcomponent_as_ical_string
    // Ensure dataflow is valid (i.e., non-null)
    if (!component) {
    	return 0;
    }
    char* ret_icalcomponent_as_ical_string_bomsq = icalcomponent_as_ical_string(component);
    if (ret_icalcomponent_as_ical_string_bomsq == NULL){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    icalpropiter iter = icalcomponent_begin_property(component, propertyKind);

    // Test icalcomponent_remove_property
    icalcomponent_remove_property(component, property);

    // Test icalcomponent_remove_property_by_kind
    icalcomponent_remove_property_by_kind(component, propertyKind);

    // Clean up
    icalproperty_free(property);
    icalcomponent_free(component);

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

    LLVMFuzzerTestOneInput_15(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
