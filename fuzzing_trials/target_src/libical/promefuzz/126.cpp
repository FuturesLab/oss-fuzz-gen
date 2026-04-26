// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalproperty_string_to_class at icalderivedproperty.c:7338:20 in icalproperty.h
// icalproperty_class_to_string at icalderivedproperty.c:7330:13 in icalproperty.h
// icalproperty_status_to_string at icalderivedproperty.c:7246:13 in icalproperty.h
// icalproperty_enum_to_string at icalderivedproperty.c:7157:13 in icalproperty.h
// icalproperty_transp_to_string at icalderivedproperty.c:7302:13 in icalproperty.h
// icalproperty_kind_to_string at icalderivedproperty.c:6996:13 in icalproperty.h
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
#include <string.h>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <icalproperty.h>

extern "C" int LLVMFuzzerTestOneInput_126(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Create a null-terminated string from the input data
    char *inputString = new char[Size + 1];
    memcpy(inputString, Data, Size);
    inputString[Size] = '\0';

    // Fuzz icalproperty_string_to_class
    icalproperty_class classResult = icalproperty_string_to_class(inputString);

    // Fuzz icalproperty_class_to_string
    const char *classString = icalproperty_class_to_string(classResult);

    // Fuzz icalproperty_kind_to_string
    if (Size >= sizeof(icalproperty_kind)) {
        icalproperty_kind kind = *reinterpret_cast<const icalproperty_kind*>(Data);
        const char *kindString = icalproperty_kind_to_string(kind);
    }

    // Fuzz icalproperty_transp_to_string
    if (Size >= sizeof(icalproperty_transp)) {
        icalproperty_transp transp = *reinterpret_cast<const icalproperty_transp*>(Data);
        const char *transpString = icalproperty_transp_to_string(transp);
    }

    // Fuzz icalproperty_status_to_string
    if (Size >= sizeof(icalproperty_status)) {
        icalproperty_status status = *reinterpret_cast<const icalproperty_status*>(Data);
        const char *statusString = icalproperty_status_to_string(status);
    }

    // Fuzz icalproperty_enum_to_string
    if (Size >= sizeof(int)) {
        int enumValue = *reinterpret_cast<const int*>(Data);
        const char *enumString = icalproperty_enum_to_string(enumValue);
    }

    delete[] inputString;
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

        LLVMFuzzerTestOneInput_126(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    