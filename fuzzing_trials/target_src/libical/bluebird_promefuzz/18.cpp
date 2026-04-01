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
#include <cassert>
#include "libical/ical.h"

static icalcomponent* create_dummy_component() {
    icalcomponent* comp = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    icalcomponent* vevent = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalcomponent_add_component(comp, vevent);
    return comp;
}

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy icalcomponent for testing
    icalcomponent* comp = create_dummy_component();

    // Test icalcomponent_get_first_real_component
    icalcomponent* first_real_comp = icalcomponent_get_first_real_component(comp);
    if (first_real_comp) {
        // Do something with first_real_comp
    }

    // Test icalcomponent_get_method
    icalproperty_method method = icalcomponent_get_method(comp);
    if (method != ICAL_METHOD_NONE) {
        // Do something with method
    }

    // Test icalcomponent_get_component_name_r
    char* component_name = icalcomponent_get_component_name_r(comp);
    if (component_name) {
        // Do something with component_name
        free(component_name);
    }

    // Test icalcomponent_get_sequence
    int sequence = icalcomponent_get_sequence(comp);
    if (sequence != 0) {
        // Do something with sequence
    }

    // Test icalcomponent_get_relcalid
    const char* relcalid = icalcomponent_get_relcalid(comp);
    if (relcalid) {
        // Do something with relcalid
    }

    // Test icalcomponent_get_summary
    const char* summary = icalcomponent_get_summary(comp);
    if (summary) {
        // Do something with summary
    }

    // Cleanup
    icalcomponent_free(comp);

    return 0;
}