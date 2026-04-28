// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalparameter_kind_value_kind at icalderivedparameter.c:2790:16 in icalparameter.h
// icalparameter_value_to_value_kind at icalderivedparameter.c:2880:16 in icalproperty.h
// icalproperty_value_kind_to_kind at icalderivedproperty.c:7032:19 in icalproperty.h
// icalvalue_kind_to_string at icalderivedvalue.c:1018:13 in icalvalue.h
// icalparameter_string_to_kind at icalderivedparameter.c:2847:20 in icalparameter.h
// icalparameter_kind_to_string at icalderivedparameter.c:2827:13 in icalparameter.h
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
#include "icalparameter.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalvalue.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalproperty.h"

extern "C" int LLVMFuzzerTestOneInput_119(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Fuzz icalparameter_kind_to_string
    icalparameter_kind param_kind = static_cast<icalparameter_kind>(Data[0]);
    const char *param_kind_str = icalparameter_kind_to_string(param_kind);
    if (param_kind_str) {
        // Ensure the returned string is not null and has a valid length
        size_t len = strlen(param_kind_str);
        (void)len;
    }

    // Fuzz icalparameter_value_to_value_kind
    if (Size < 2) return 0;
    icalparameter_value param_value = static_cast<icalparameter_value>(Data[1]);
    icalvalue_kind value_kind = icalparameter_value_to_value_kind(param_value);
    (void)value_kind;

    // Fuzz icalproperty_value_kind_to_kind
    if (Size < 3) return 0;
    icalvalue_kind val_kind = static_cast<icalvalue_kind>(Data[2]);
    icalproperty_kind prop_kind = icalproperty_value_kind_to_kind(val_kind);
    (void)prop_kind;

    // Fuzz icalparameter_string_to_kind
    if (Size > 0) {
        // Ensure null-termination and a reasonable length for the test string
        size_t max_test_str_len = std::min(Size, static_cast<size_t>(256));
        std::string test_str(reinterpret_cast<const char*>(Data), max_test_str_len);
        icalparameter_kind str_to_kind = icalparameter_string_to_kind(test_str.c_str());
        (void)str_to_kind;
    }

    // Fuzz icalvalue_kind_to_string
    if (Size < 4) return 0;
    icalvalue_kind value_kind2 = static_cast<icalvalue_kind>(Data[3]);
    const char *value_kind_str = icalvalue_kind_to_string(value_kind2);
    if (value_kind_str) {
        size_t len = strlen(value_kind_str);
        (void)len;
    }

    // Fuzz icalparameter_kind_value_kind
    int is_multivalued = 0;
    icalvalue_kind kind_value_kind = icalparameter_kind_value_kind(param_kind, &is_multivalued);
    (void)kind_value_kind;
    (void)is_multivalued;

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

        LLVMFuzzerTestOneInput_119(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    