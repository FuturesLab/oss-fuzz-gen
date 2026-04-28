// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalproperty_enum_belongs_to_property at icalderivedproperty.c:7204:6 in icalproperty.h
// icalproperty_kind_is_valid at icalderivedproperty.c:6977:10 in icalproperty.h
// icalparameter_kind_is_valid at icalderivedparameter.c:2809:6 in icalparameter.h
// icalproperty_string_to_kind at icalderivedproperty.c:7010:19 in icalproperty.h
// icalproperty_kind_to_string at icalderivedproperty.c:6996:13 in icalproperty.h
// icalcomponent_remove_property_by_kind at icalcomponent.c:425:6 in icalcomponent.h
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
#include <fstream>
#include <string>
#include <cstring>
#include <cassert>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalparameter.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalproperty.h"

extern "C" int LLVMFuzzerTestOneInput_47(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Fuzz icalproperty_kind_to_string
    icalproperty_kind kind = static_cast<icalproperty_kind>(Data[0]);
    const char *kind_str = icalproperty_kind_to_string(kind);
    if (kind_str != nullptr) {
        std::string kindStr(kind_str);
        // Use the string representation
    }

    // Fuzz icalproperty_string_to_kind
    std::string inputStr(reinterpret_cast<const char*>(Data), Size);
    icalproperty_kind kind_from_str = icalproperty_string_to_kind(inputStr.c_str());

    // Fuzz icalparameter_kind_is_valid
    icalparameter_kind param_kind = static_cast<icalparameter_kind>(Data[0]);
    bool is_valid_param_kind = icalparameter_kind_is_valid(param_kind);

    // Fuzz icalproperty_enum_belongs_to_property
    if (Size > 1) {
        int enum_value = static_cast<int>(Data[1]);
        bool belongs = icalproperty_enum_belongs_to_property(kind, enum_value);
    }

    // Fuzz icalcomponent_remove_property_by_kind
    // Create a dummy icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component) {
        icalcomponent_remove_property_by_kind(component, kind);
        icalcomponent_free(component);
    }

    // Fuzz icalproperty_kind_is_valid
    bool is_valid_kind = icalproperty_kind_is_valid(kind);

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

        LLVMFuzzerTestOneInput_47(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    