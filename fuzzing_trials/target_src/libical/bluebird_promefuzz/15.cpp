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
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalcomponent.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalrestriction.h"

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(icalcomponent_kind) + 5) {
        return 0;
    }

    // Prepare the component
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(Data[4]);
    icalcomponent *component = icalcomponent_new(kind);
    if (!component) {
        return 0;
    }

    // Set a dummy ID
    char id[5];
    memcpy(id, Data, 4);
    id[4] = '\0';  // Null-terminate the ID

    // Assuming there's a way to set the ID in icalcomponent, which might be a custom method
    // For the sake of this example, we assume that the ID is part of the component's properties

    // Fuzz icalcomponent_is_valid
    bool is_valid = icalcomponent_is_valid(component);

    // Fuzz icalrestriction_check
    bool restriction_check = icalrestriction_check(component);

    // Fuzz icalcomponent_set_status
    if (Size > 5) {
        icalproperty_status status = static_cast<icalproperty_status>(Data[5]);
        icalcomponent_set_status(component, status);
    }

    // Fuzz icalcomponent_isa_component
    bool isa_component = icalcomponent_isa_component(component);

    // Fuzz icalcomponent_normalize
    icalcomponent_normalize(component);

    // Fuzz icalcomponent_check_restrictions

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_normalize to icalproperty_set_parent
    const char hjwgssdy[1024] = "uzfgc";
    icalproperty* ret_icalproperty_vanew_allowconflict_gqlps = icalproperty_vanew_allowconflict(hjwgssdy);
    if (ret_icalproperty_vanew_allowconflict_gqlps == NULL){
    	return 0;
    }
    // Ensure dataflow is valid (i.e., non-null)
    if (!ret_icalproperty_vanew_allowconflict_gqlps) {
    	return 0;
    }
    // Ensure dataflow is valid (i.e., non-null)
    if (!component) {
    	return 0;
    }
    icalproperty_set_parent(ret_icalproperty_vanew_allowconflict_gqlps, component);
    // End mutation: Producer.APPEND_MUTATOR
    
    bool check_restrictions = icalcomponent_check_restrictions(component);

    // Clean up
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_15(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
