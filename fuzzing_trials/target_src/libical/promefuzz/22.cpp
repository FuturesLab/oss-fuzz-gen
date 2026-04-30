// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalproperty_get_value_as_string at icalproperty.c:819:13 in icalproperty.h
// icalproperty_get_property_name_r at icalproperty.c:868:7 in icalproperty.h
// icalproperty_set_x_name at icalproperty.c:839:6 in icalproperty.h
// icalproperty_get_property_name at icalproperty.c:859:13 in icalproperty.h
// icalproperty_remove_parameter_by_name at icalproperty.c:641:6 in icalproperty.h
// icalproperty_get_value_as_string_r at icalproperty.c:828:7 in icalproperty.h
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
#include <cstring>
#include <cstdint>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <icalproperty.h>

extern "C" int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy icalproperty
    icalproperty *prop = icalproperty_new(ICAL_X_PROPERTY);
    if (!prop) return 0;

    // Use part of the input data as a string
    std::string inputStr(reinterpret_cast<const char*>(Data), Size);

    // Test icalproperty_set_x_name
    icalproperty_set_x_name(prop, inputStr.c_str());

    // Test icalproperty_get_value_as_string_r
    char *valueStr = icalproperty_get_value_as_string_r(prop);
    if (valueStr) {
        free(valueStr);
    }

    // Test icalproperty_get_property_name_r
    char *nameStr = icalproperty_get_property_name_r(prop);
    if (nameStr) {
        free(nameStr);
    }

    // Test icalproperty_remove_parameter_by_name
    icalproperty_remove_parameter_by_name(prop, inputStr.c_str());

    // Test icalproperty_get_value_as_string
    const char *valueConstStr = icalproperty_get_value_as_string(prop);
    if (valueConstStr) {
        // Normally managed by the library, no need to free
    }

    // Test icalproperty_get_property_name
    const char *nameConstStr = icalproperty_get_property_name(prop);
    if (nameConstStr) {
        // Normally managed by the library, no need to free
    }

    // Clean up
    icalproperty_free(prop);

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

        LLVMFuzzerTestOneInput_22(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    