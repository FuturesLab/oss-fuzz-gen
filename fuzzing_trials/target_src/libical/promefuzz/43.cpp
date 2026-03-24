// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_new_xavailable at icalcomponent.c:2090:16 in icalcomponent.h
// icalcomponent_new_vagenda at icalcomponent.c:2070:16 in icalcomponent.h
// icalcomponent_new_vfreebusy at icalcomponent.c:2050:16 in icalcomponent.h
// icalcomponent_new_vavailability at icalcomponent.c:2085:16 in icalcomponent.h
// icalcomponent_vanew at icalcomponent.c:105:16 in icalcomponent.h
// icalcomponent_new_vjournal at icalcomponent.c:2040:16 in icalcomponent.h
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
#include <cstddef>
#include "ical.h"
#include <cstdarg>

extern "C" int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Test icalcomponent_new_vavailability
    icalcomponent *vavailability = icalcomponent_new_vavailability();
    if (vavailability) {
        icalcomponent_free(vavailability);
    }

    // Test icalcomponent_new_vfreebusy
    icalcomponent *vfreebusy = icalcomponent_new_vfreebusy();
    if (vfreebusy) {
        icalcomponent_free(vfreebusy);
    }

    // Test icalcomponent_new_vagenda
    icalcomponent *vagenda = icalcomponent_new_vagenda();
    if (vagenda) {
        icalcomponent_free(vagenda);
    }

    // Test icalcomponent_vanew with a random kind from the input data
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES);
    icalcomponent *vanew = icalcomponent_vanew(kind, nullptr);
    if (vanew) {
        icalcomponent_free(vanew);
    }

    // Test icalcomponent_new_xavailable
    icalcomponent *xavailable = icalcomponent_new_xavailable();
    if (xavailable) {
        icalcomponent_free(xavailable);
    }

    // Test icalcomponent_new_vjournal
    icalcomponent *vjournal = icalcomponent_new_vjournal();
    if (vjournal) {
        icalcomponent_free(vjournal);
    }

    return 0;
}