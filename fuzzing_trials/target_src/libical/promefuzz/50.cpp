// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_set_relcalid at icalcomponent.c:2573:6 in icalcomponent.h
// icalcomponent_set_uid at icalcomponent.c:1804:6 in icalcomponent.h
// icalcomponent_set_location at icalcomponent.c:1920:6 in icalcomponent.h
// icalcomponent_set_comment at icalcomponent.c:1769:6 in icalcomponent.h
// icalcomponent_set_summary at icalcomponent.c:1734:6 in icalcomponent.h
// icalcomponent_set_description at icalcomponent.c:1885:6 in icalcomponent.h
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
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    icalcomponent_kind kind = static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES);
    icalcomponent *comp = icalcomponent_new(kind);
    if (!comp) return 0;

    char *null_terminated_str = static_cast<char*>(malloc(Size + 1));
    if (!null_terminated_str) {
        icalcomponent_free(comp);
        return 0;
    }
    
    memcpy(null_terminated_str, Data, Size);
    null_terminated_str[Size] = '\0';

    // Test icalcomponent_set_uid
    icalcomponent_set_uid(comp, null_terminated_str);

    // Test icalcomponent_set_relcalid
    icalcomponent_set_relcalid(comp, null_terminated_str);

    // Test icalcomponent_set_comment
    icalcomponent_set_comment(comp, null_terminated_str);

    // Test icalcomponent_set_description
    icalcomponent_set_description(comp, null_terminated_str);

    // Test icalcomponent_set_location
    icalcomponent_set_location(comp, null_terminated_str);

    // Test icalcomponent_set_summary
    icalcomponent_set_summary(comp, null_terminated_str);

    free(null_terminated_str);
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

        LLVMFuzzerTestOneInput_50(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    