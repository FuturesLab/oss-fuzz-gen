#include <stdint.h>
#include <stddef.h>
#include "libical/ical.h"

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    // Initialize variables
    icalcomponent *component;
    int sequence;

    // Ensure size is sufficient to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Create a dummy icalcomponent
    component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Extract an integer from the input data
    sequence = *(reinterpret_cast<const int*>(data));

    // Call the function-under-test
    icalcomponent_set_sequence(component, sequence);

    // Clean up
    icalcomponent_free(component);

    return 0;
}