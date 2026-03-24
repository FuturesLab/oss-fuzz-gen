// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcompiter_prior at icalcomponent.c:1406:16 in icalcomponent.h
// icalcompiter_next at icalcomponent.c:1387:16 in icalcomponent.h
// icalcompiter_deref at icalcomponent.c:1425:16 in icalcomponent.h
// icalcomponent_begin_component at icalcomponent.c:1342:14 in icalcomponent.h
// icalcompiter_is_valid at icalcomponent.c:1336:6 in icalcomponent.h
// icalcomponent_get_first_component at icalcomponent.c:611:16 in icalcomponent.h
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

static icalcomponent* create_dummy_component() {
    return icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
}

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    std::ofstream file("./dummy_file", std::ios::binary);
    file.write(reinterpret_cast<const char*>(Data), Size);
    file.close();
}

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Write data to dummy file if needed
    write_dummy_file(Data, Size);

    // Create a dummy icalcomponent
    icalcomponent *comp = create_dummy_component();
    if (!comp) return 0;

    // Begin component iteration
    icalcompiter iter = icalcomponent_begin_component(comp, ICAL_ANY_COMPONENT);

    // Check the validity of the iterator
    bool is_valid = icalcompiter_is_valid(&iter);
    if (is_valid) {
        // Retrieve the first component
        icalcomponent *first_comp = icalcomponent_get_first_component(comp, ICAL_ANY_COMPONENT);

        // Iterate over components
        while (icalcompiter_is_valid(&iter)) {
            icalcomponent *current_comp = icalcompiter_deref(&iter);
            if (current_comp) {
                // Do something with the current component
            }
            icalcompiter_next(&iter);
        }

        // Go backwards using icalcompiter_prior
        icalcomponent *prior_comp = icalcompiter_prior(&iter);
        if (prior_comp) {
            // Do something with the prior component
        }
    }

    // Clean up
    icalcomponent_free(comp);

    return 0;
}