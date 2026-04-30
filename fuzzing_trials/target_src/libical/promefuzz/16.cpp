// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalpropiter_deref at icalcomponent.c:1479:15 in icalcomponent.h
// icalpropiter_next at icalcomponent.c:1460:15 in icalcomponent.h
// icalcomponent_get_current_property at icalcomponent.c:463:15 in icalcomponent.h
// icalproperty_get_parent at icalproperty.c:907:16 in icalcomponent.h
// icalcomponent_remove_property at icalcomponent.c:400:6 in icalcomponent.h
// icalproperty_set_parent at icalproperty.c:900:6 in icalcomponent.h
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
#include "icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(icalcomponent_kind) + sizeof(icalproperty_kind)) {
        return 0;
    }

    // Prepare environment
    icalcomponent_kind comp_kind = static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES);
    icalproperty_kind prop_kind = static_cast<icalproperty_kind>((Data[1] % ICAL_NO_PROPERTY) + 1);

    icalcomponent *component = icalcomponent_new(comp_kind);
    icalproperty *property = icalproperty_new(prop_kind);

    if (!component || !property) {
        if (component) icalcomponent_free(component);
        if (property) icalproperty_free(property);
        return 0;
    }

    // Set parent
    icalproperty_set_parent(property, component);

    // Get parent
    icalcomponent *parent = icalproperty_get_parent(property);

    // Use iterators
    icalpropiter iter;
    iter.kind = ICAL_ANY_PROPERTY;
    iter.iter = nullptr;

    icalproperty *current_prop = icalcomponent_get_current_property(component);
    if (current_prop) {
        icalproperty *deref_prop = icalpropiter_deref(&iter);
        icalproperty *next_prop = icalpropiter_next(&iter);
    }

    // Remove property
    icalcomponent_remove_property(component, property);

    // Cleanup
    icalproperty_free(property); // Ensure property is freed before the component
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

        LLVMFuzzerTestOneInput_16(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    