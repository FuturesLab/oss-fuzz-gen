// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icallangbind_get_next_property at icallangbind.c:82:15 in icallangbind.h
// icallangbind_get_first_property at icallangbind.c:57:15 in icallangbind.h
// icalproperty_set_value_from_string at icalproperty.c:771:6 in icalproperty.h
// icalproperty_get_x_name at icalproperty.c:852:13 in icalproperty.h
// icalproperty_set_parameter_from_string at icalproperty.c:507:6 in icalproperty.h
// icalproperty_get_property_name_r at icalproperty.c:868:7 in icalproperty.h
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
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icallangbind.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalproperty.h"

extern "C" int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy icalproperty
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);
    if (!prop) return 0;

    // Create a dummy icalcomponent
    icalcomponent *comp = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    if (!comp) {
        icalproperty_free(prop);
        return 0;
    }

    // Prepare strings from Data
    size_t halfSize = Size / 2;
    char *name = new char[halfSize + 1];
    char *value = new char[Size - halfSize + 1];
    memcpy(name, Data, halfSize);
    memcpy(value, Data + halfSize, Size - halfSize);
    name[halfSize] = '\0';
    value[Size - halfSize] = '\0';

    // Test icalproperty_get_property_name_r
    char *property_name = icalproperty_get_property_name_r(prop);
    if (property_name) {
        free(property_name);
    }

    // Test icalproperty_get_x_name
    const char *x_name = icalproperty_get_x_name(prop);

    // Test icalproperty_set_parameter_from_string
    icalproperty_set_parameter_from_string(prop, name, value);

    // Test icallangbind_get_first_property
    icalproperty *first_prop = icallangbind_get_first_property(comp, name);

    // Test icallangbind_get_next_property
    icalproperty *next_prop = icallangbind_get_next_property(comp, name);

    // Test icalproperty_set_value_from_string
    icalproperty_set_value_from_string(prop, value, name);

    // Clean up
    delete[] name;
    delete[] value;
    icalproperty_free(prop);
    icalcomponent_free(comp);

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

        LLVMFuzzerTestOneInput_50(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    