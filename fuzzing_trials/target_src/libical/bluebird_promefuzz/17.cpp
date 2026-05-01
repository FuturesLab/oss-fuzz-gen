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

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_new_from_string to icalcomponent_set_dtstart
    struct icaltimetype ret_icalcomponent_get_due_jgzmi = icalcomponent_get_due(NULL);
    // Ensure dataflow is valid (i.e., non-null)
    if (!comp) {
    	return 0;
    }
    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalcomponent_set_dtstart with icalcomponent_set_dtend
    icalcomponent_set_dtend(comp, ret_icalcomponent_get_due_jgzmi);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR
    // End mutation: Producer.APPEND_MUTATOR
    
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
        icalcomponent_kind_is_valid(kind);

        // Test icalcomponent_is_valid
        icalcomponent_is_valid(comp);

        // Cleanup the component
        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalcomponent_free with icalcomponent_normalize
        icalcomponent_normalize(comp);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR
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

    LLVMFuzzerTestOneInput_17(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
