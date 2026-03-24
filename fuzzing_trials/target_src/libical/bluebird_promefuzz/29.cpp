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
#include <string>
#include <cstddef>
#include <cstdint>
#include "libical/ical.h"
#include <cstdlib>
#include <cstring>
#include <cstdarg>

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(icalcomponent_kind) + 1) {
        return 0;
    }

    icalcomponent_kind kind = static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES);
    icalcomponent *comp = icalcomponent_vanew(kind, NULL);

    if (!comp) {
        return 0;
    }

    // Test icalcomponent_normalize
    icalcomponent_normalize(comp);

    // Test icalcomponent_check_restrictions
    bool check_passed = icalcomponent_check_restrictions(comp);

    // Test icalcomponent_new_participant
    icalcomponent *participant = icalcomponent_new_participant();
    if (participant) {
        icalcomponent_add_component(comp, participant);
    }

    // Test icalcomponent_strip_errors
    icalcomponent_strip_errors(comp);

    // Test icalcomponent_is_valid
    bool is_valid = icalcomponent_is_valid(comp);

    // Clean up
    icalcomponent_free(comp);

    return 0;
}