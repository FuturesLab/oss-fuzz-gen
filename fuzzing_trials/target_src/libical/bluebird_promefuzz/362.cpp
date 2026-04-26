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
#include <cstddef>
#include <cstring>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalcomponent.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalparameter.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalvalue.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalproperty.h"

extern "C" int LLVMFuzzerTestOneInput_362(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Fuzzing icalcomponent_kind_to_string
    icalcomponent_kind componentKind = static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES);
    const char *componentKindStr = icalcomponent_kind_to_string(componentKind);
    if (componentKindStr) {
        size_t len = strlen(componentKindStr);
        volatile char tmp = componentKindStr[len - 1];  // Force read to avoid optimization
    }

    // Ensure null-termination for string operations
    std::string dataStr(reinterpret_cast<const char*>(Data), Size);
    dataStr.push_back('\0');

    // Fuzzing icalvalue_string_to_kind
    icalvalue_kind valueKind = icalvalue_string_to_kind(dataStr.c_str());

    // Fuzzing icalparameter_kind_to_string
    icalparameter_kind parameterKind = static_cast<icalparameter_kind>(Data[0] % ICAL_NO_PARAMETER);
    const char *parameterKindStr = icalparameter_kind_to_string(parameterKind);
    if (parameterKindStr) {
        size_t len = strlen(parameterKindStr);
        volatile char tmp = parameterKindStr[len - 1];  // Force read to avoid optimization
    }

    // Fuzzing icalvalue_kind_to_string
    icalvalue_kind valueKindForString = static_cast<icalvalue_kind>(Data[0] % ICAL_NO_VALUE);
    const char *valueKindStr = icalvalue_kind_to_string(valueKindForString);
    if (valueKindStr) {
        size_t len = strlen(valueKindStr);
        volatile char tmp = valueKindStr[len - 1];  // Force read to avoid optimization
    }

    // Fuzzing icalcomponent_string_to_kind
    icalcomponent_kind componentKindFromString = icalcomponent_string_to_kind(dataStr.c_str());

    // Fuzzing icalproperty_kind_to_value_kind
    icalproperty_kind propertyKind = static_cast<icalproperty_kind>(Data[0] % (ICAL_NO_PROPERTY + 1));
    icalvalue_kind defaultValueKind = icalproperty_kind_to_value_kind(propertyKind);

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

    LLVMFuzzerTestOneInput_362(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
