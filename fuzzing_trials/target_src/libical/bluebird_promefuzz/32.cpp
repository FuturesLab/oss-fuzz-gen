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
#include <cstring>
#include "libical/ical.h"

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(icalcomponent_kind)) {
        return 0;
    }

    // Prepare a dummy icalcomponent
    icalcomponent *component = icalcomponent_new(static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES));
    if (component) {
        // Test icalcomponent_get_current_component
        icalcomponent *current_component = icalcomponent_get_current_component(component);

        // Test icalcomponent_is_valid
        bool is_valid_component = icalcomponent_is_valid(component);

        // Test icalcomponent_get_current_property
        icalproperty *current_property = icalcomponent_get_current_property(component);

        // Prepare a dummy icalcompiter
        icalcompiter compiter;
        memset(&compiter, 0, sizeof(compiter));
        compiter.kind = static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES);

        // Test icalcompiter_deref
        icalcomponent *deref_component = icalcompiter_deref(&compiter);

        // Test icalcompiter_is_valid
        bool is_valid_compiter = icalcompiter_is_valid(&compiter);

        // Prepare a dummy icalpropiter
        icalpropiter propiter;
        memset(&propiter, 0, sizeof(propiter));
        propiter.kind = static_cast<icalproperty_kind>(Data[0] % ICAL_NO_PROPERTY);

        // Test icalpropiter_is_valid
        bool is_valid_propiter = icalpropiter_is_valid(&propiter);

        // Clean up the component
        icalcomponent_free(component);
    }

    return 0;
}