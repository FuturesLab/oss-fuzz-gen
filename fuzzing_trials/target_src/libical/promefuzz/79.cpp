// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalparameter_kind_to_string at icalderivedparameter.c:2827:13 in icalparameter.h
// icalparameter_string_to_kind at icalderivedparameter.c:2847:20 in icalparameter.h
// icalparameter_new_from_value_string at icalderivedparameter.c:3011:16 in icalparameter.h
// icalparameter_decode_value at icalparameter.c:411:6 in icalparameter.h
// icalparameter_as_ical_string at icalparameter.c:172:7 in icalparameter.h
// icalparameter_get_iana_value at icalparameter.c:341:13 in icalparameter.h
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
#include <cstring>
#include <cassert>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <icalparameter.h>

extern "C" int LLVMFuzzerTestOneInput_79(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0; // Ensure there's at least one byte for kind and one for value

    // Fuzz icalparameter_new_from_value_string
    icalparameter_kind kind = static_cast<icalparameter_kind>(Data[0] % ICAL_NO_PARAMETER);
    char *value = nullptr;
    if (Size > 1) {
        // Dynamically allocate memory for the value string to ensure it remains valid
        value = static_cast<char*>(malloc(Size));
        if (value) {
            memcpy(value, Data + 1, Size - 1);
            value[Size - 1] = '\0'; // Null-terminate the string
        }
    }
    icalparameter *param = icalparameter_new_from_value_string(kind, value);
    if (param) {
        // Fuzz icalparameter_as_ical_string
        char *icalStr = icalparameter_as_ical_string(param);
        if (icalStr) {
            // Normally we would do something with icalStr
        }

        // Fuzz icalparameter_get_iana_value
        const char *ianaValue = icalparameter_get_iana_value(param);
        if (ianaValue) {
            // Normally we would do something with ianaValue
        }

        icalparameter_free(param);
    }

    // Fuzz icalparameter_kind_to_string
    const char *kindStr = icalparameter_kind_to_string(kind);
    if (kindStr) {
        // Normally we would do something with kindStr
    }

    // Fuzz icalparameter_string_to_kind
    if (value) {
        icalparameter_kind kindFromString = icalparameter_string_to_kind(value);
        // Normally we would do something with kindFromString
    }

    // Fuzz icalparameter_decode_value
    if (value) {
        char *mutableValue = strdup(value);
        if (mutableValue) {
            icalparameter_decode_value(mutableValue);
            free(mutableValue);
        }
    }

    if (value) {
        free(value); // Free the dynamically allocated memory
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

        LLVMFuzzerTestOneInput_79(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    