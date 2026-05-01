// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_count_components at icalcomponent.c:583:5 in icalcomponent.h
// icalcomponent_count_errors at icalcomponent.c:1123:5 in icalcomponent.h
// icalcomponent_count_properties at icalcomponent.c:447:5 in icalcomponent.h
// icalcomponent_clone at icalcomponent.c:129:16 in icalcomponent.h
// icalcomponent_get_first_real_component at icalcomponent.c:647:16 in icalcomponent.h
// icalcomponent_check_restrictions at icalcomponent.c:1117:6 in icalcomponent.h
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Create a dummy icalcomponent from input data
    icalcomponent *component = icalcomponent_new(ICAL_NO_COMPONENT);
    if (!component) {
        return 0;
    }

    // Fuzz icalcomponent_count_properties
    for (int kind = ICAL_ANY_PROPERTY; kind <= ICAL_NO_PROPERTY; ++kind) {
        int property_count = icalcomponent_count_properties(component, static_cast<icalproperty_kind>(kind));
        (void)property_count;
    }

    // Fuzz icalcomponent_count_errors
    int error_count = icalcomponent_count_errors(component);
    (void)error_count;

    // Fuzz icalcomponent_count_components
    for (int kind = ICAL_NO_COMPONENT; kind < ICAL_NUM_COMPONENT_TYPES; ++kind) {
        int component_count = icalcomponent_count_components(component, static_cast<icalcomponent_kind>(kind));
        (void)component_count;
    }

    // Fuzz icalcomponent_clone
    icalcomponent *cloned_component = icalcomponent_clone(component);
    if (cloned_component) {
        icalcomponent_free(cloned_component);
    }

    // Fuzz icalcomponent_check_restrictions
    bool restrictions_ok = icalcomponent_check_restrictions(component);
    (void)restrictions_ok;

    // Fuzz icalcomponent_get_first_real_component
    icalcomponent *first_real_component = icalcomponent_get_first_real_component(component);
    if (first_real_component) {
        // Do something with the first real component if needed
    }

    // Clean up
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

        LLVMFuzzerTestOneInput_8(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    