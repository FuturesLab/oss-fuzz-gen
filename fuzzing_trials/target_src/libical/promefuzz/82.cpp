// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalvalue_as_ical_string_r at icalvalue.c:1206:7 in icalvalue.h
// icalvalue_as_ical_string at icalvalue.c:1197:13 in icalvalue.h
// icalvalue_new_from_string at icalvalue.c:780:12 in icalvalue.h
// icalvalue_free at icalvalue.c:785:6 in icalvalue.h
// icalvalue_clone at icalvalue.c:58:12 in icalvalue.h
// icalvalue_new at icalvalue.c:53:12 in icalvalue.h
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
#include "icalvalue.h"

extern "C" int LLVMFuzzerTestOneInput_82(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Select a kind from the data
    icalvalue_kind kind = static_cast<icalvalue_kind>(Data[0] % ICAL_NO_VALUE);

    // Create a string from the remaining data
    char *str = nullptr;
    if (Size > 1) {
        str = static_cast<char*>(malloc(Size));
        if (!str) {
            return 0;
        }
        memcpy(str, Data + 1, Size - 1);
        str[Size - 1] = '\0';
    }

    // Fuzz icalvalue_new_from_string
    icalvalue *value_from_string = icalvalue_new_from_string(kind, str);

    // Fuzz icalvalue_clone
    if (value_from_string) {
        icalvalue *cloned_value = icalvalue_clone(value_from_string);
        if (cloned_value) {
            icalvalue_free(cloned_value);
        }
    }

    // Fuzz icalvalue_new
    icalvalue *new_value = icalvalue_new(kind);

    // Fuzz icalvalue_as_ical_string_r
    if (new_value) {
        char *ical_string_r = icalvalue_as_ical_string_r(new_value);
        free(ical_string_r);
    }

    // Fuzz icalvalue_as_ical_string
    if (new_value) {
        const char *ical_string = icalvalue_as_ical_string(new_value);
        // Note: No need to free ical_string as it is managed internally
    }

    // Cleanup
    if (value_from_string) {
        icalvalue_free(value_from_string);
    }
    if (new_value) {
        icalvalue_free(new_value);
    }
    free(str);

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

        LLVMFuzzerTestOneInput_82(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    