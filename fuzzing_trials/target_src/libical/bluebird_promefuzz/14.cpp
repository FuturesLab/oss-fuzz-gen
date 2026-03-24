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
#include "libical/ical.h"

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    // Initialize components
    icalcomponent *vavailability = icalcomponent_new_vavailability();
    icalcomponent *vcalendar = icalcomponent_new_vcalendar();

    // Test icalcomponent_get_span with vavailability
    struct icaltime_span span = icalcomponent_get_span(vavailability);

    // Test icalcomponent_get_span with vcalendar
    span = icalcomponent_get_span(vcalendar);

    // Test icalcomponent_get_current_component
    icalcomponent *current_component = icalcomponent_get_current_component(vcalendar);

    // Test icalcomponent_is_valid
    bool is_valid = icalcomponent_is_valid(vavailability);
    is_valid = icalcomponent_is_valid(vcalendar);

    // Test icalcomponent_clone
    icalcomponent *cloned_vavailability = icalcomponent_clone(vavailability);
    icalcomponent *cloned_vcalendar = icalcomponent_clone(vcalendar);

    // Clean up
    icalcomponent_free(vavailability);
    icalcomponent_free(vcalendar);
    if (cloned_vavailability) {
        icalcomponent_free(cloned_vavailability);
    }
    if (cloned_vcalendar) {
        icalcomponent_free(cloned_vcalendar);
    }

    return 0;
}