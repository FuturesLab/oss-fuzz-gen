#include <sys/stat.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <stdint.h>
#include <stddef.h>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalproperty.h"
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_367(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) {
        return 0;
    }

    // Fuzz icalproperty_enum_to_string_r
    int enum_value = *(reinterpret_cast<const int*>(Data));
    char *enum_string_r = icalproperty_enum_to_string_r(enum_value);
    if (enum_string_r) {
        free(enum_string_r);
    }

    // Fuzz icalproperty_enum_to_string
    const char *enum_string = icalproperty_enum_to_string(enum_value);
    (void)enum_string; // Use the result to avoid compiler warnings

    // Prepare a dummy icalproperty for other tests
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);
    if (!prop) {
        return 0;
    }

    // Fuzz icalproperty_get_parameter_as_string_r
    if (Size > sizeof(int)) {
        const char *param_name = reinterpret_cast<const char*>(Data + sizeof(int));
        char *param_string_r = icalproperty_get_parameter_as_string_r(prop, param_name);
        if (param_string_r) {
            free(param_string_r);
        }
    }

    // Fuzz icalproperty_get_value_as_string_r
    char *value_string_r = icalproperty_get_value_as_string_r(prop);
    if (value_string_r) {
        free(value_string_r);
    }

    // Fuzz icalproperty_as_ical_string_r
    char *ical_string_r = icalproperty_as_ical_string_r(prop);
    if (ical_string_r) {
        free(ical_string_r);
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_367(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
