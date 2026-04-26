// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalreqstattype_from_string at icaltypes.c:91:24 in icaltypes.h
// icalreqstattype_as_string_r at icaltypes.c:157:7 in icaltypes.h
// icalreqstattype_as_string at icaltypes.c:148:13 in icaltypes.h
// icalenum_reqstat_code_r at icalenums.c:92:7 in icalenums.h
// icalenum_reqstat_desc at icalenums.c:69:13 in icalenums.h
// icalenum_reqstat_code at icalenums.c:83:7 in icalenums.h
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
#include "icaltypes.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalenums.h"

extern "C" int LLVMFuzzerTestOneInput_73(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Fuzz icalenum_reqstat_code
    icalrequeststatus status = static_cast<icalrequeststatus>(Data[0]);
    char *code = icalenum_reqstat_code(status);
    // No need to free code as it is managed by libical's memory management

    // Fuzz icalenum_reqstat_desc
    const char *desc = icalenum_reqstat_desc(status);
    // No need to free desc as it's a const char*

    // Fuzz icalreqstattype_from_string
    char *str = (char *)malloc(Size + 1);
    if (!str) return 0;
    memcpy(str, Data, Size);
    str[Size] = '\0';
    icalreqstattype reqstattype = icalreqstattype_from_string(str);
    free(str);

    // Fuzz icalreqstattype_as_string_r
    char *reqstat_string_r = icalreqstattype_as_string_r(reqstattype);
    if (reqstat_string_r) {
        free(reqstat_string_r);
    }

    // Fuzz icalreqstattype_as_string
    const char *reqstat_string = icalreqstattype_as_string(reqstattype);
    // No need to free reqstat_string as it's a const char*

    // Fuzz icalenum_reqstat_code_r
    char *code_r = icalenum_reqstat_code_r(status);
    if (code_r) {
        free(code_r);
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

        LLVMFuzzerTestOneInput_73(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    