// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalparameter_isa at icalparameter.c:272:20 in icalparameter.h
// icalparameter_new at icalparameter.c:44:16 in icalparameter.h
// icalparameter_new_from_value_string at icalderivedparameter.c:3011:16 in icalparameter.h
// icalparameter_clone at icalparameter.c:79:16 in icalparameter.h
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
#include <cstring>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalparameter.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalproperty.h"

extern "C" int LLVMFuzzerTestOneInput_87(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Ensure there's at least one byte to work with

    // Use the first byte to determine the kind
    icalparameter_kind kind = static_cast<icalparameter_kind>(Data[0] % ICAL_NO_PARAMETER);

    // Create a null-terminated string from the remaining data
    std::string value(reinterpret_cast<const char*>(Data + 1), Size - 1);

    // Test icalparameter_new_from_value_string
    icalparameter *param = icalparameter_new_from_value_string(kind, value.c_str());
    if (param) {
        // Test icalparameter_clone
        icalparameter *clone = icalparameter_clone(param);
        if (clone) {
            // Test icalparameter_isa
            icalparameter_kind cloned_kind = icalparameter_isa(clone);
            (void)cloned_kind; // Use the cloned_kind to avoid unused variable warning

            // Free the cloned parameter
            icalparameter_free(clone);
        }

        // Free the original parameter
        icalparameter_free(param);
    }

    // Test icalparameter_new
    icalparameter *new_param = icalparameter_new(kind);
    if (new_param) {
        // Test icalparameter_isa
        icalparameter_kind new_kind = icalparameter_isa(new_param);
        (void)new_kind; // Use the new_kind to avoid unused variable warning

        // Free the new parameter
        icalparameter_free(new_param);
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

        LLVMFuzzerTestOneInput_87(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    