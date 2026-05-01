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

extern "C" int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Use the first byte to determine the icalcomponent_kind
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES);

    // Test icalcomponent_new
    icalcomponent *comp = icalcomponent_new(kind);
    if (!comp) {
        return 0;
    }

    // Test icalcomponent_kind_to_string

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_new to icalcomponent_set_parent
    // Ensure dataflow is valid (i.e., non-null)
    if (!comp) {
    	return 0;
    }
    struct icaltimetype ret_icalcomponent_get_due_dzkgq = icalcomponent_get_due(comp);
    // Ensure dataflow is valid (i.e., non-null)
    if (!comp) {
    	return 0;
    }
    // Ensure dataflow is valid (i.e., non-null)
    if (!comp) {
    	return 0;
    }
    icalcomponent_set_parent(comp, comp);
    // End mutation: Producer.APPEND_MUTATOR
    
    const char *kind_str = icalcomponent_kind_to_string(kind);

    // Test icalcomponent_isa
    icalcomponent_kind comp_kind = icalcomponent_isa(comp);

    // Test icalcomponent_set_description
    if (Size > 1) {
        // Ensure the description is null-terminated
        size_t desc_len = Size - 1;
        char *description = static_cast<char *>(malloc(desc_len + 1));
        if (description) {
            memcpy(description, Data + 1, desc_len);
            description[desc_len] = '\0';
            icalcomponent_set_description(comp, description);
            free(description);
        }
    }

    // Test icalcomponent_string_to_kind
    if (kind_str) {
        icalcomponent_kind kind_from_str = icalcomponent_string_to_kind(kind_str);
    }

    // Test icalcomponent_kind_is_valid
    bool is_valid = icalcomponent_kind_is_valid(kind);

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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_34(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
