// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_get_method at icalcomponent.c:1511:21 in icalcomponent.h
// icalcomponent_set_method at icalcomponent.c:1499:6 in icalcomponent.h
// icalcomponent_new_vpatch at icalcomponent.c:2110:16 in icalcomponent.h
// icalcomponent_new_vcalendar at icalcomponent.c:2025:16 in icalcomponent.h
// icalcomponent_get_inner at icalcomponent.c:1490:16 in icalcomponent.h
// icalcomponent_add_component at icalcomponent.c:509:6 in icalcomponent.h
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
#include <fstream>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"

static void test_icalcomponent_set_get_method(icalcomponent *comp, icalproperty_method method) {
    icalcomponent_set_method(comp, method);
    icalproperty_method retrieved_method = icalcomponent_get_method(comp);
    if (retrieved_method != method) {
        std::cerr << "Method mismatch: set " << method << ", got " << retrieved_method << std::endl;
    }
}

static void test_icalcomponent_add_get_inner(icalcomponent *parent, icalcomponent *child) {
    icalcomponent_add_component(parent, child);
    icalcomponent *inner = icalcomponent_get_inner(parent);
    if (inner != child) {
        std::cerr << "Inner component mismatch" << std::endl;
    }
}

extern "C" int LLVMFuzzerTestOneInput_96(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a new VCALENDAR component
    icalcomponent *vcalendar = icalcomponent_new_vcalendar();
    if (!vcalendar) return 0;

    // Create a new VPATCH component
    icalcomponent *vpatch = icalcomponent_new_vpatch();
    if (!vpatch) {
        icalcomponent_free(vcalendar);
        return 0;
    }

    // Use the first byte of Data to set a method
    icalproperty_method method = static_cast<icalproperty_method>(Data[0] % (ICAL_METHOD_NONE + 1));
    test_icalcomponent_set_get_method(vcalendar, method);

    // Add VPATCH to VCALENDAR and test inner component retrieval
    test_icalcomponent_add_get_inner(vcalendar, vpatch);

    // Clean up
    // Free the parent component which will also free the child components
    icalcomponent_free(vcalendar);

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

        LLVMFuzzerTestOneInput_96(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    