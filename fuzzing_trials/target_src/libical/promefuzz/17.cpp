// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_count_properties at icalcomponent.c:447:5 in icalcomponent.h
// icalcomponent_remove_property_by_kind at icalcomponent.c:425:6 in icalcomponent.h
// icalcomponent_begin_property at icalcomponent.c:1436:14 in icalcomponent.h
// icalcomponent_get_next_property at icalcomponent.c:489:15 in icalcomponent.h
// icalcomponent_get_first_property at icalcomponent.c:474:15 in icalcomponent.h
// icalcomponent_add_property at icalcomponent.c:385:6 in icalcomponent.h
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
#include <vector>
#include <cstdlib>
#include <cstring>
#include "ical.h"

static icalcomponent* create_dummy_component() {
    icalcomponent* component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component) {
        icalproperty* prop = icalproperty_new_summary("Dummy Summary");
        icalcomponent_add_property(component, prop);
    }
    return component;
}

static void fuzz_icalcomponent_functions(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    icalcomponent* component = create_dummy_component();
    if (!component) return;

    icalproperty_kind kind = static_cast<icalproperty_kind>(Data[0] % ICAL_NO_PROPERTY);

    // Test icalcomponent_begin_property
    icalpropiter iter = icalcomponent_begin_property(component, kind);

    // Test icalcomponent_get_next_property
    icalproperty* next_prop = icalcomponent_get_next_property(component, kind);

    // Test icalcomponent_get_first_property
    icalproperty* first_prop = icalcomponent_get_first_property(component, kind);

    // Test icalcomponent_count_properties
    int count = icalcomponent_count_properties(component, kind);

    // Test icalcomponent_remove_property_by_kind
    icalcomponent_remove_property_by_kind(component, kind);

    // Clean up
    icalcomponent_free(component);
}

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    fuzz_icalcomponent_functions(Data, Size);
    return 0;
}