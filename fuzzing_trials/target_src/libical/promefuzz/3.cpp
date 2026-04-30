// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalparameter_get_parent at icalparameter.c:363:15 in icalproperty.h
// icalparameter_set_parent at icalparameter.c:356:6 in icalproperty.h
// icallangbind_get_next_parameter at icallangbind.c:46:16 in icallangbind.h
// icalproperty_set_parameter at icalproperty.c:488:6 in icalproperty.h
// icalproperty_remove_parameter_by_ref at icalproperty.c:671:6 in icalproperty.h
// icallangbind_get_first_parameter at icallangbind.c:39:16 in icallangbind.h
#include <iostream>
#include <cstring>
#include <cstdint>
extern "C" {
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icallangbind.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalproperty.h"
}

static void fuzz_icalparameter_set_parent(icalparameter *param, icalproperty *property) {
    icalparameter_set_parent(param, property);
}

static void fuzz_icallangbind_get_next_parameter(icalproperty *property) {
    icalparameter *param = icallangbind_get_next_parameter(property);
    if (param) {
        // Further operations can be done with param if needed
    }
}

static void fuzz_icallangbind_get_first_parameter(icalproperty *property) {
    icalparameter *param = icallangbind_get_first_parameter(property);
    if (param) {
        // Further operations can be done with param if needed
    }
}

static void fuzz_icalproperty_set_parameter(icalproperty *property, icalparameter *parameter) {
    icalproperty_set_parameter(property, parameter);
}

static void fuzz_icalproperty_remove_parameter_by_ref(icalproperty *property, icalparameter *parameter) {
    icalproperty_remove_parameter_by_ref(property, parameter);
}

static void fuzz_icalparameter_get_parent(icalparameter *parameter) {
    icalproperty *property = icalparameter_get_parent(parameter);
    if (property) {
        // Further operations can be done with property if needed
    }
}

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(icalparameter_kind) + sizeof(icalvalue_kind)) {
        return 0; // Not enough data for meaningful fuzzing
    }

    // Create dummy icalparameter and icalproperty objects
    icalparameter *param = icalparameter_new(ICAL_ANY_PARAMETER);
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);

    if (!param || !property) {
        if (param) icalparameter_free(param);
        if (property) icalproperty_free(property);
        return 0;
    }

    // Fuzz each function with the data provided
    fuzz_icalparameter_set_parent(param, property);
    fuzz_icallangbind_get_next_parameter(property);
    fuzz_icallangbind_get_first_parameter(property);
    fuzz_icalproperty_set_parameter(property, param);
    fuzz_icalproperty_remove_parameter_by_ref(property, param);
    fuzz_icalparameter_get_parent(param);

    // Clean up
    icalparameter_free(param);
    icalproperty_free(property);

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

        LLVMFuzzerTestOneInput_3(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    