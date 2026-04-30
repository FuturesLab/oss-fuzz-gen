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
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalproperty.h"

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Prepare a null-terminated string for icalproperty_new_from_string
    char *icalStr = new char[Size + 1];
    memcpy(icalStr, Data, Size);
    icalStr[Size] = '\0';

    // Test icalproperty_new_from_string
    icalproperty *prop = icalproperty_new_from_string(icalStr);

    // If property creation was successful, perform further operations
    if (prop) {
        // Test icalproperty_remove_parameter_by_kind with a random parameter kind
        icalproperty_remove_parameter_by_kind(prop, ICAL_TZID_PARAMETER);

        // Test icalproperty_normalize
        icalproperty_normalize(prop);

        // Test icalproperty_clone
        icalproperty *clonedProp = icalproperty_clone(prop);
        if (clonedProp) {
            icalproperty_free(clonedProp);
        }


        // Begin mutation: Producer.SPLICE_MUTATOR - Spliced data flow from icalproperty_clone to icalproperty_get_property_name_r using the plateau pool
        // Ensure dataflow is valid (i.e., non-null)
        if (!clonedProp) {
        	return 0;
        }
        char* ret_icalproperty_get_property_name_r_ikbwj = icalproperty_get_property_name_r(clonedProp);
        if (ret_icalproperty_get_property_name_r_ikbwj == NULL){
        	return 0;
        }
        // End mutation: Producer.SPLICE_MUTATOR
        
        icalproperty_free(prop);
    }

    // Test icalproperty_new with a random property kind
    icalproperty *newProp = icalproperty_new(ICAL_SUMMARY_PROPERTY);
    if (newProp) {
        icalproperty_free(newProp);
    }

    delete[] icalStr;
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

    LLVMFuzzerTestOneInput_11(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
