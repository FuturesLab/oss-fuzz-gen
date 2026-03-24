// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_normalize at icalcomponent.c:2832:6 in icalcomponent.h
// icalcomponent_new_participant at icalcomponent.c:2120:16 in icalcomponent.h
// icalcomponent_new_xdaylight at icalcomponent.c:2065:16 in icalcomponent.h
// icalcomponent_new_valarm at icalcomponent.c:2045:16 in icalcomponent.h
// icalcomponent_vanew at icalcomponent.c:105:16 in icalcomponent.h
// icalcomponent_set_uid at icalcomponent.c:1804:6 in icalcomponent.h
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
#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include "ical.h"

static void fuzz_icalcomponent_normalize(icalcomponent *comp) {
    if (comp) {
        icalcomponent_normalize(comp);
    }
}

static void fuzz_icalcomponent_set_uid(icalcomponent *comp, const char *uid) {
    if (comp && uid) {
        icalcomponent_set_uid(comp, uid);
    }
}

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a new VALARM component
    icalcomponent *valarm = icalcomponent_new_valarm();
    fuzz_icalcomponent_normalize(valarm);

    // Create a new PARTICIPANT component
    icalcomponent *participant = icalcomponent_new_participant();
    fuzz_icalcomponent_normalize(participant);

    // Create a new XDAYLIGHT component
    icalcomponent *xdaylight = icalcomponent_new_xdaylight();
    fuzz_icalcomponent_normalize(xdaylight);

    // Use a portion of the input data to set a UID
    size_t uid_length = Size > 32 ? 32 : Size;
    char *uid = static_cast<char *>(malloc(uid_length + 1));
    if (uid) {
        memcpy(uid, Data, uid_length);
        uid[uid_length] = '\0';
        fuzz_icalcomponent_set_uid(valarm, uid);
        fuzz_icalcomponent_set_uid(participant, uid);
        fuzz_icalcomponent_set_uid(xdaylight, uid);
        free(uid);
    }

    // Create a new complex component using icalcomponent_vanew
    icalcomponent *complex_component = icalcomponent_vanew(
        ICAL_VEVENT_COMPONENT,
        valarm,
        participant,
        xdaylight,
        NULL
    );

    if (complex_component) {
        fuzz_icalcomponent_normalize(complex_component);
        icalcomponent_free(complex_component);
    } else {
        // If complex_component creation failed, free individual components
        if (valarm) {
            icalcomponent_free(valarm);
        }
        if (participant) {
            icalcomponent_free(participant);
        }
        if (xdaylight) {
            icalcomponent_free(xdaylight);
        }
    }

    return 0;
}