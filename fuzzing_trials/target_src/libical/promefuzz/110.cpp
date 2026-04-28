// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalproperty_clone at icalproperty.c:92:15 in icalproperty.h
// icalproperty_normalize at icalproperty.c:921:6 in icalproperty.h
// icalproperty_free at icalproperty.c:176:6 in icalproperty.h
// icalproperty_new at icalproperty.c:83:15 in icalproperty.h
// icalproperty_isa at icalproperty.c:459:19 in icalproperty.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
extern "C" {
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <icalproperty.h>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
}

static icalproperty_kind getRandomKind(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return ICAL_NO_PROPERTY;
    return static_cast<icalproperty_kind>(Data[0] % 136);  // 136 is the number of kinds defined
}

extern "C" int LLVMFuzzerTestOneInput_110(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    icalproperty_kind kind = getRandomKind(Data, Size);
    icalproperty *prop = icalproperty_new(kind);
    if (!prop) return 0;

    // Fuzz icalproperty_normalize
    icalproperty_normalize(prop);

    // Fuzz icalproperty_isa
    icalproperty_kind kind_result = icalproperty_isa(prop);

    // Fuzz icalproperty_clone
    icalproperty *cloned_prop = icalproperty_clone(prop);
    if (cloned_prop) {
        icalproperty_free(cloned_prop);
    }

    // Clean up
    icalproperty_free(prop);

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

        LLVMFuzzerTestOneInput_110(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    