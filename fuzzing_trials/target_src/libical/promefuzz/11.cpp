// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_is_valid at icalcomponent.c:295:6 in icalcomponent.h
// icalcomponent_check_restrictions at icalcomponent.c:1117:6 in icalcomponent.h
// icalcomponent_strip_errors at icalcomponent.c:1145:6 in icalcomponent.h
// icalcomponent_new_participant at icalcomponent.c:2120:16 in icalcomponent.h
// icalcomponent_normalize at icalcomponent.c:2832:6 in icalcomponent.h
// icalcomponent_vanew at icalcomponent.c:105:16 in icalcomponent.h
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
#include "ical.h"
#include <cstdlib>
#include <cstring>
#include <cstdarg>

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
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