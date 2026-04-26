// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalproperty_remove_parameter_by_kind at icalproperty.c:624:6 in icalproperty.h
// icalproperty_free at icalproperty.c:176:6 in icalproperty.h
// icalproperty_normalize at icalproperty.c:921:6 in icalproperty.h
// icalproperty_clone at icalproperty.c:92:15 in icalproperty.h
// icalproperty_new_from_string at icalproperty.c:130:15 in icalproperty.h
// icalproperty_new at icalproperty.c:83:15 in icalproperty.h
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
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalproperty.h"

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
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

        if(size < 1 + 1)
            exit(0);

        data = (uint8_t *)malloc((size_t)size);
        if(data == NULL)
            exit(0);

        if(fread(data, (size_t)size, 1, f) != 1)
            exit(0);

        LLVMFuzzerTestOneInput_26(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    