#include <sys/stat.h>
#include <string.h>
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
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalvalue.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalproperty.h"

extern "C" int LLVMFuzzerTestOneInput_168(const uint8_t *Data, size_t Size) {
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_168(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
