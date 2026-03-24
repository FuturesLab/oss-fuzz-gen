// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_new_vpoll at icalcomponent.c:2095:16 in icalcomponent.h
// icalcomponent_new_vavailability at icalcomponent.c:2085:16 in icalcomponent.h
// icalcomponent_new_vcalendar at icalcomponent.c:2025:16 in icalcomponent.h
// icalcomponent_clone at icalcomponent.c:129:16 in icalcomponent.h
// icalcomponent_new_vreply at icalcomponent.c:2080:16 in icalcomponent.h
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
#include <iostream>
#include <fstream>
#include "ical.h"

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Create different components using the target API functions
    icalcomponent *vavailability = icalcomponent_new_vavailability();
    icalcomponent *vcalendar = icalcomponent_new_vcalendar();
    icalcomponent *vreply = icalcomponent_new_vreply();
    icalcomponent *vpoll = icalcomponent_new_vpoll();
    icalcomponent *vresource = icalcomponent_new_vresource();

    // Clone the created components to explore different states
    icalcomponent *cloned_vavailability = icalcomponent_clone(vavailability);
    icalcomponent *cloned_vcalendar = icalcomponent_clone(vcalendar);
    icalcomponent *cloned_vreply = icalcomponent_clone(vreply);
    icalcomponent *cloned_vpoll = icalcomponent_clone(vpoll);
    icalcomponent *cloned_vresource = icalcomponent_clone(vresource);

    // Clean up the created components
    icalcomponent_free(vavailability);
    icalcomponent_free(vcalendar);
    icalcomponent_free(vreply);
    icalcomponent_free(vpoll);
    icalcomponent_free(vresource);

    icalcomponent_free(cloned_vavailability);
    icalcomponent_free(cloned_vcalendar);
    icalcomponent_free(cloned_vreply);
    icalcomponent_free(cloned_vpoll);
    icalcomponent_free(cloned_vresource);

    return 0;
}