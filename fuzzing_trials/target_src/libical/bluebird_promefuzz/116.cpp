#include <sys/stat.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_116(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(icalcomponent_kind)) {
        return 0;
    }

    // Prepare an icalcomponent
    icalcomponent_kind kind;
    memcpy(&kind, Data, sizeof(icalcomponent_kind));
    Data += sizeof(icalcomponent_kind);
    Size -= sizeof(icalcomponent_kind);

    icalcomponent *comp = icalcomponent_new(kind);
    if (!comp) {
        return 0;
    }

    // Use the remaining data to create dummy properties or comments
    if (Size > 0) {
        char *dummyData = (char *)malloc(Size + 1);
        if (dummyData) {
            memcpy(dummyData, Data, Size);
            dummyData[Size] = '\0';

            // Set a dummy comment
            icalcomponent_set_comment(comp, dummyData);

            // Set a dummy UID
            icalcomponent_set_uid(comp, dummyData);

            // Clean up
            free(dummyData);
        }
    }

    // Fuzz the API functions
    char *icalStringR = icalcomponent_as_ical_string_r(comp);
    if (icalStringR) {
        free(icalStringR);
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_as_ical_string_r to icalproperty_set_capversion
    const char irtypigu[1024] = "hrepb";
    icalproperty* ret_icalproperty_vanew_patchversion_zptld = icalproperty_vanew_patchversion(irtypigu);
    if (ret_icalproperty_vanew_patchversion_zptld == NULL){
    	return 0;
    }
    // Ensure dataflow is valid (i.e., non-null)
    if (!ret_icalproperty_vanew_patchversion_zptld) {
    	return 0;
    }
    // Ensure dataflow is valid (i.e., non-null)
    if (!icalStringR) {
    	return 0;
    }
    icalproperty_set_capversion(ret_icalproperty_vanew_patchversion_zptld, icalStringR);
    // End mutation: Producer.APPEND_MUTATOR
    
    const char *comment = icalcomponent_get_comment(comp);
    if (comment) {
        // Do something with comment if needed
    }

    const char *componentName = icalcomponent_get_component_name(comp);
    if (componentName) {
        // Do something with componentName if needed
    }

    const char *relcalid = icalcomponent_get_relcalid(comp);
    if (relcalid) {
        // Do something with relcalid if needed
    }

    char *icalString = icalcomponent_as_ical_string(comp);
    if (icalString) {
        free(icalString);
    }

    const char *uid = icalcomponent_get_uid(comp);
    if (uid) {
        // Do something with uid if needed
    }

    // Clean up
    icalcomponent_free(comp);

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

    LLVMFuzzerTestOneInput_116(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
