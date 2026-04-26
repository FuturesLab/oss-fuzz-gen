// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalproperty_get_allow_empty_properties at icalproperty.c:64:6 in icalproperty.h
// icaltimezone_get_builtin_tzdata at icaltimezone.c:2293:6 in icaltimezone.h
// icaltimezone_set_builtin_tzdata at icaltimezone.c:2288:6 in icaltimezone.h
// icalproperty_set_allow_empty_properties at icalproperty.c:59:6 in icalproperty.h
// icalerror_get_errors_are_fatal at icalerror.c:105:6 in icalerror.h
// icalerror_set_errors_are_fatal at icalerror.c:100:6 in icalerror.h
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
#include <icalerror.h>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <icalproperty.h>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <icaltimezone.h>
}

extern "C" int LLVMFuzzerTestOneInput_115(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Use the first byte of the input data to determine boolean values
    bool toggle = Data[0] % 2 == 0;

    // Fuzz icaltimezone_get_builtin_tzdata
    bool tzdata_enabled = icaltimezone_get_builtin_tzdata();

    // Fuzz icalerror_get_errors_are_fatal
    bool errors_fatal = icalerror_get_errors_are_fatal();

    // Fuzz icalerror_set_errors_are_fatal
    icalerror_set_errors_are_fatal(toggle);

    // Fuzz icaltimezone_set_builtin_tzdata
    icaltimezone_set_builtin_tzdata(toggle);

    // Fuzz icalproperty_get_allow_empty_properties
    bool allow_empty_properties = icalproperty_get_allow_empty_properties();

    // Fuzz icalproperty_set_allow_empty_properties
    icalproperty_set_allow_empty_properties(toggle);

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

        LLVMFuzzerTestOneInput_115(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    