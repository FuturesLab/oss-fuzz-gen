// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_get_first_property at icalcomponent.c:474:15 in icalcomponent.h
// icalcomponent_get_next_property at icalcomponent.c:489:15 in icalcomponent.h
// icalcomponent_get_current_property at icalcomponent.c:463:15 in icalcomponent.h
// icalcomponent_remove_property at icalcomponent.c:400:6 in icalcomponent.h
// icalproperty_set_parent at icalproperty.c:900:6 in icalcomponent.h
// icalproperty_get_parent at icalproperty.c:907:16 in icalcomponent.h
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
#include <icalcomponent.h>

extern "C" int LLVMFuzzerTestOneInput_88(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (!component) return 0;

    icalproperty *property = icalproperty_new(ICAL_SUMMARY_PROPERTY);
    if (!property) {
        icalcomponent_free(component);
        return 0;
    }

    // Set the parent of the property
    icalproperty_set_parent(property, component);

    // Get the first property of any kind
    icalproperty *first_property = icalcomponent_get_first_property(component, ICAL_ANY_PROPERTY);

    // Traverse all properties
    icalproperty *current_property = first_property;
    while (current_property != NULL) {
        current_property = icalcomponent_get_next_property(component, ICAL_ANY_PROPERTY);
    }

    // Retrieve the current property
    icalproperty *current = icalcomponent_get_current_property(component);

    // Get the parent from the property
    icalcomponent *parent = icalproperty_get_parent(property);

    // Remove the property from the component
    icalcomponent_remove_property(component, property);

    // Free the property and component
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

        LLVMFuzzerTestOneInput_88(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    