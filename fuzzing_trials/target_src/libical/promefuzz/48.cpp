// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalproperty_value_kind_to_kind at icalderivedproperty.c:7032:19 in icalproperty.h
// icalproperty_kind_to_value_kind at icalderivedproperty.c:7046:16 in icalproperty.h
// icalparameter_value_to_value_kind at icalderivedparameter.c:2880:16 in icalproperty.h
// icalvalue_string_to_kind at icalderivedvalue.c:1032:16 in icalvalue.h
// icalvalue_kind_to_string at icalderivedvalue.c:1018:13 in icalvalue.h
// icalvalue_isa at icalvalue.c:1306:16 in icalvalue.h
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
#include <iostream>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalvalue.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalproperty.h"

extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Prepare a null-terminated string from the input data
    char *inputString = new char[Size + 1];
    memcpy(inputString, Data, Size);
    inputString[Size] = '\0';

    // 1. Test icalvalue_string_to_kind
    icalvalue_kind kindFromString = icalvalue_string_to_kind(inputString);
    (void)kindFromString; // Use the result to avoid unused variable warning

    // 2. Test icalvalue_isa
    icalvalue *value = icalvalue_new(kindFromString);
    if (value) {
        icalvalue_kind kindFromValue = icalvalue_isa(value);
        (void)kindFromValue; // Use the result to avoid unused variable warning
        icalvalue_free(value);
    }

    // 3. Test icalparameter_value_to_value_kind
    if (Size >= sizeof(icalparameter_value)) {
        icalparameter_value paramValue;
        memcpy(&paramValue, Data, sizeof(icalparameter_value));
        icalvalue_kind kindFromParam = icalparameter_value_to_value_kind(paramValue);
        (void)kindFromParam; // Use the result to avoid unused variable warning
    }

    // 4. Test icalproperty_value_kind_to_kind
    icalproperty_kind propKind = icalproperty_value_kind_to_kind(kindFromString);
    (void)propKind; // Use the result to avoid unused variable warning

    // 5. Test icalvalue_kind_to_string
    const char *kindString = icalvalue_kind_to_string(kindFromString);
    if (kindString) {
        (void)kindString; // Use the result to avoid unused variable warning
    }

    // 6. Test icalproperty_kind_to_value_kind
    icalvalue_kind defaultValueKind = icalproperty_kind_to_value_kind(propKind);
    (void)defaultValueKind; // Use the result to avoid unused variable warning

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

        LLVMFuzzerTestOneInput_48(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    