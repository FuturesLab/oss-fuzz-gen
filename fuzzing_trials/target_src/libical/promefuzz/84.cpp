// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_count_properties at icalcomponent.c:447:5 in icalcomponent.h
// icalcomponent_get_sequence at icalcomponent.c:1967:5 in icalcomponent.h
// icalcomponent_count_errors at icalcomponent.c:1123:5 in icalcomponent.h
// icalcomponent_count_components at icalcomponent.c:583:5 in icalcomponent.h
// icalcomponent_remove_component at icalcomponent.c:543:6 in icalcomponent.h
// icalcomponent_set_parent at icalcomponent.c:1231:6 in icalcomponent.h
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
#include <iostream>
#include <fstream>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_84(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file if necessary
    std::ofstream dummyFile("./dummy_file");
    dummyFile.write(reinterpret_cast<const char*>(Data), Size);
    dummyFile.close();

    // Initialize an icalcomponent (assuming a function to create it)
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);

    // Fuzz icalcomponent_count_components
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES);
    int count = icalcomponent_count_components(component, kind);
    std::cout << "Count Components: " << count << std::endl;

    // Fuzz icalcomponent_count_properties
    icalproperty_kind prop_kind = static_cast<icalproperty_kind>(Data[0] % ICAL_NO_PROPERTY);
    int prop_count = icalcomponent_count_properties(component, prop_kind);
    std::cout << "Count Properties: " << prop_count << std::endl;

    // Fuzz icalcomponent_remove_component
    icalcomponent *child_component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalcomponent_remove_component(component, child_component);

    // Fuzz icalcomponent_get_sequence
    int sequence = icalcomponent_get_sequence(component);
    std::cout << "Get Sequence: " << sequence << std::endl;

    // Fuzz icalcomponent_count_errors
    int error_count = icalcomponent_count_errors(component);
    std::cout << "Count Errors: " << error_count << std::endl;

    // Fuzz icalcomponent_set_parent
    icalcomponent *parent_component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    icalcomponent_set_parent(child_component, parent_component);

    // Cleanup
    icalcomponent_free(component);
    icalcomponent_free(child_component);
    icalcomponent_free(parent_component);

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

        LLVMFuzzerTestOneInput_84(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    