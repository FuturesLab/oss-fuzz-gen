// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalproperty_add_parameter at icalproperty.c:480:6 in icalproperty.h
// icalparameter_set_parent at icalparameter.c:356:6 in icalproperty.h
// icallangbind_get_first_parameter at icallangbind.c:39:16 in icallangbind.h
// icalproperty_remove_parameter_by_ref at icalproperty.c:671:6 in icalproperty.h
// icalparameter_get_parent at icalparameter.c:363:15 in icalproperty.h
// icallangbind_get_next_parameter at icallangbind.c:46:16 in icallangbind.h
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
#include "icallangbind.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalproperty.h"

static icalproperty* create_random_icalproperty() {
    return icalproperty_new(ICAL_ANY_PROPERTY);
}

static icalparameter* create_random_icalparameter() {
    return icalparameter_new(ICAL_ANY_PARAMETER);
}

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    icalproperty *prop = create_random_icalproperty();
    icalparameter *param = create_random_icalparameter();

    if (prop && param) {
        // Fuzz icalproperty_add_parameter
        icalproperty_add_parameter(prop, param);

        // Fuzz icalparameter_set_parent
        icalparameter_set_parent(param, prop);

        // Fuzz icallangbind_get_first_parameter
        icalparameter *first_param = icallangbind_get_first_parameter(prop);

        // Fuzz icallangbind_get_next_parameter
        icalparameter *next_param = icallangbind_get_next_parameter(prop);

        // Fuzz icalproperty_remove_parameter_by_ref
        if (first_param) {
            icalproperty_remove_parameter_by_ref(prop, first_param);
        }

        // Fuzz icalparameter_get_parent
        icalproperty *parent_prop = icalparameter_get_parent(param);
    }

    if (prop) {
        icalproperty_free(prop);
    }
    if (param) {
        icalparameter_free(param);
    }

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

        LLVMFuzzerTestOneInput_5(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    