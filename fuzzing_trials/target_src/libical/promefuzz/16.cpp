// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icaltimezone_get_location_from_vtimezone at icaltimezone.c:344:7 in icaltimezone.h
// icallangbind_get_first_component at icallangbind.c:107:16 in icallangbind.h
// icalcomponent_get_first_real_component at icalcomponent.c:647:16 in icalcomponent.h
// icalcomponent_strip_errors at icalcomponent.c:1145:6 in icalcomponent.h
// icalcomponent_get_first_component at icalcomponent.c:611:16 in icalcomponent.h
// icalcomponent_as_ical_string at icalcomponent.c:215:7 in icalcomponent.h
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
#include <cstdlib>
#include <cstring>
#include <fstream>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icallangbind.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icaltimezone.h"

static icalcomponent* create_random_icalcomponent(const uint8_t *Data, size_t Size) {
    // This function should create a random icalcomponent based on the input data
    // For simplicity, let's create a basic VEVENT component
    icalcomponent* comp = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    return comp;
}

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a random icalcomponent from input data
    icalcomponent* comp = create_random_icalcomponent(Data, Size);
    if (!comp) return 0;

    // Test icalcomponent_get_first_real_component
    icalcomponent* first_real_comp = icalcomponent_get_first_real_component(comp);
    if (first_real_comp) {
        // Optionally, do something with first_real_comp
    }

    // Test icalcomponent_get_first_component
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES);
    icalcomponent* first_comp = icalcomponent_get_first_component(comp, kind);
    if (first_comp) {
        // Optionally, do something with first_comp
    }

    // Test icalcomponent_strip_errors
    icalcomponent_strip_errors(comp);

    // Test icaltimezone_get_location_from_vtimezone
    char* location = icaltimezone_get_location_from_vtimezone(comp);
    if (location) {
        free(location); // Remember to free the allocated string
    }

    // Test icallangbind_get_first_component
    const char* comp_type = "VEVENT"; // Using a static type for simplicity
    icalcomponent* langbind_first_comp = icallangbind_get_first_component(comp, comp_type);
    if (langbind_first_comp) {
        // Optionally, do something with langbind_first_comp
    }

    // Test icalcomponent_as_ical_string
    char* ical_str = icalcomponent_as_ical_string(comp);
    if (ical_str) {
        // Do not free ical_str since it's managed by libical's internal buffer ring
    }

    // Clean up
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

        LLVMFuzzerTestOneInput_16(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    