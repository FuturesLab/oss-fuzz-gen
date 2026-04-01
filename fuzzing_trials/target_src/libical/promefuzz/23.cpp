// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_string_to_kind at icalcomponent.c:1319:20 in icalcomponent.h
// icalcomponent_kind_to_string at icalcomponent.c:1306:13 in icalcomponent.h
// icalcomponent_get_summary at icalcomponent.c:1746:13 in icalcomponent.h
// icalcomponent_as_ical_string_r at icalcomponent.c:226:7 in icalcomponent.h
// icalcomponent_get_component_name_r at icalcomponent.c:353:7 in icalcomponent.h
// icalcomponent_get_sequence at icalcomponent.c:1967:5 in icalcomponent.h
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

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Prepare a null-terminated string for icalcomponent_string_to_kind
    char *inputString = static_cast<char*>(malloc(Size + 1));
    if (!inputString) return 0;
    memcpy(inputString, Data, Size);
    inputString[Size] = '\0';

    // Test icalcomponent_string_to_kind
    icalcomponent_kind kind = icalcomponent_string_to_kind(inputString);
    free(inputString);

    // Test icalcomponent_kind_to_string
    const char *kindString = icalcomponent_kind_to_string(kind);

    // Create a dummy icalcomponent for testing
    icalcomponent *component = icalcomponent_new(kind);

    if (component) {
        // Test icalcomponent_get_component_name_r
        char *componentName = icalcomponent_get_component_name_r(component);
        if (componentName) {
            free(componentName);
        }

        // Test icalcomponent_get_sequence
        int sequence = icalcomponent_get_sequence(component);

        // Test icalcomponent_as_ical_string_r
        char *icalString = icalcomponent_as_ical_string_r(component);
        if (icalString) {
            free(icalString);
        }

        // Test icalcomponent_get_summary
        const char *summary = icalcomponent_get_summary(component);

        // Clean up
        icalcomponent_free(component);
    }

    return 0;
}