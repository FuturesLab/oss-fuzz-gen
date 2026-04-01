// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_new_xpatch at icalcomponent.c:2115:16 in icalcomponent.h
// icalcomponent_new_vfreebusy at icalcomponent.c:2050:16 in icalcomponent.h
// icalcomponent_new_vquery at icalcomponent.c:2075:16 in icalcomponent.h
// icalcomponent_new_vtodo at icalcomponent.c:2035:16 in icalcomponent.h
// icalcomponent_new_vpatch at icalcomponent.c:2110:16 in icalcomponent.h
// icalcomponent_new_vresource at icalcomponent.c:2130:16 in icalcomponent.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "ical.h"

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    // Initialize components
    icalcomponent *vquery = nullptr;
    icalcomponent *vfreebusy = nullptr;
    icalcomponent *vpatch = nullptr;
    icalcomponent *vtodo = nullptr;
    icalcomponent *xpatch = nullptr;
    icalcomponent *vresource = nullptr;

    // Try to create each component and handle potential NULL returns
    vquery = icalcomponent_new_vquery();
    if (vquery) {
        icalcomponent_free(vquery);
    }

    vfreebusy = icalcomponent_new_vfreebusy();
    if (vfreebusy) {
        icalcomponent_free(vfreebusy);
    }

    vpatch = icalcomponent_new_vpatch();
    if (vpatch) {
        icalcomponent_free(vpatch);
    }

    vtodo = icalcomponent_new_vtodo();
    if (vtodo) {
        icalcomponent_free(vtodo);
    }

    xpatch = icalcomponent_new_xpatch();
    if (xpatch) {
        icalcomponent_free(xpatch);
    }

    vresource = icalcomponent_new_vresource();
    if (vresource) {
        icalcomponent_free(vresource);
    }

    return 0;
}