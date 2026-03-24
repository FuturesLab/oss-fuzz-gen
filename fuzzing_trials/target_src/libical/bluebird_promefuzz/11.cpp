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
#include <cstring>
#include "libical/ical.h"

static icalcomponent* create_dummy_component() {
    icalcomponent* component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    if (!component) {
        return nullptr;
    }
    icalcomponent* subcomponent = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (subcomponent) {
        icalcomponent_add_component(component, subcomponent);
    }
    return component;
}

static void fuzz_icalcomponent_functions(const uint8_t *Data, size_t Size) {
    // Use a dummy component for testing
    icalcomponent* component = create_dummy_component();
    if (!component) {
        return;
    }

    // Randomly choose a component kind for testing
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES);
    
    // Test icalcomponent_begin_component
    icalcompiter iter = icalcomponent_begin_component(component, kind);
    
    // Test icalcomponent_get_current_component
    icalcomponent* current = icalcomponent_get_current_component(component);
    
    // Test icalcomponent_get_first_component
    icalcomponent* first = icalcomponent_get_first_component(component, kind);
    
    // Test icalcompiter_next
    icalcomponent* next = icalcompiter_next(&iter);
    
    // Test icalcompiter_deref
    icalcomponent* deref = icalcompiter_deref(&iter);
    
    // Test icalcomponent_end_component
    icalcompiter end_iter = icalcomponent_end_component(component, kind);

    // Clean up
    icalcomponent_free(component);
}

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;
    fuzz_icalcomponent_functions(Data, Size);
    return 0;
}