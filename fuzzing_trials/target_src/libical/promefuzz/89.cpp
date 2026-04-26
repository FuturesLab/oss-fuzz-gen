// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_isa_component at icalcomponent.c:311:6 in icalcomponent.h
// icalproperty_isa_property at icalproperty.c:468:6 in icalproperty.h
// icalcomponent_add_property at icalcomponent.c:385:6 in icalcomponent.h
// icalcomponent_remove_property at icalcomponent.c:400:6 in icalcomponent.h
// icalproperty_remove_parameter_by_kind at icalproperty.c:624:6 in icalproperty.h
// icalcomponent_get_current_property at icalcomponent.c:463:15 in icalcomponent.h
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
#include <cstdint>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalproperty.h"

extern "C" int LLVMFuzzerTestOneInput_89(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare a dummy icalproperty and icalcomponent
    icalproperty *property = icalproperty_new(static_cast<icalproperty_kind>(Data[0] % ICAL_NO_PROPERTY));
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    if (!property || !component) {
        if (property) icalproperty_free(property);
        if (component) icalcomponent_free(component);
        return 0;
    }

    // Test icalproperty_isa_property
    bool is_prop = icalproperty_isa_property(property);

    // Test icalcomponent_isa_component
    bool is_comp = icalcomponent_isa_component(component);

    // Test icalproperty_remove_parameter_by_kind
    if (Size > 1) {
        icalparameter_kind kind = static_cast<icalparameter_kind>(Data[1] % ICAL_NO_PARAMETER);
        icalproperty_remove_parameter_by_kind(property, kind);
    }

    // Test icalcomponent_add_property
    icalcomponent_add_property(component, property);

    // Test icalcomponent_remove_property
    icalcomponent_remove_property(component, property);

    // Test icalcomponent_get_current_property
    icalproperty *current_property = icalcomponent_get_current_property(component);

    // Cleanup
    icalproperty_free(property);
    icalcomponent_free(component);

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

        LLVMFuzzerTestOneInput_89(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    