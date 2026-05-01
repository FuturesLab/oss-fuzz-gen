// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalpropiter_deref at icalcomponent.c:1479:15 in icalcomponent.h
// icalpropiter_next at icalcomponent.c:1460:15 in icalcomponent.h
// icalcomponent_get_current_property at icalcomponent.c:463:15 in icalcomponent.h
// icalcomponent_remove_property at icalcomponent.c:400:6 in icalcomponent.h
// icalproperty_get_parent at icalproperty.c:907:16 in icalcomponent.h
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
#include <iostream>
#include <fstream>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"

static icalcomponent* create_dummy_component() {
    icalcomponent* component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (!component) return nullptr;

    icalproperty* property = icalproperty_new(ICAL_SUMMARY_PROPERTY);
    if (!property) {
        icalcomponent_free(component);
        return nullptr;
    }
    icalcomponent_add_property(component, property);
    return component;
}

static icalproperty* create_dummy_property(icalcomponent* parent) {
    icalproperty* property = icalproperty_new(ICAL_DESCRIPTION_PROPERTY);
    if (property && parent) {
        icalproperty_set_parent(property, parent);
    }
    return property;
}

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    icalcomponent* component = create_dummy_component();
    if (!component) return 0;

    icalproperty* property = create_dummy_property(component);
    if (!property) {
        icalcomponent_free(component);
        return 0;
    }

    icalcomponent* parent = icalproperty_get_parent(property);
    if (parent != component) {
        std::cerr << "Parent component mismatch" << std::endl;
    }

    icalpropiter iter;
    iter.kind = static_cast<icalproperty_kind>(Data[0] % ICAL_NO_PROPERTY);
    iter.iter = nullptr;

    icalproperty* iter_property = icalpropiter_deref(&iter);
    if (iter_property) {
        icalcomponent_remove_property(component, iter_property);
    }

    iter_property = icalpropiter_next(&iter);
    if (iter_property) {
        icalcomponent_remove_property(component, iter_property);
    }

    icalproperty* current_property = icalcomponent_get_current_property(component);
    if (current_property) {
        icalcomponent_remove_property(component, current_property);
    }

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

        LLVMFuzzerTestOneInput_19(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    