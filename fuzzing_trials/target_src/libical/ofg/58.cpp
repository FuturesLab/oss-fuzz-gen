#include <stdint.h>
#include <stdlib.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Initialize an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Extract an integer from the input data
    int sequence = *(reinterpret_cast<const int*>(data));

    // Call the function under test
    icalcomponent_set_sequence(component, sequence);

    // Clean up
    icalcomponent_free(component);

    return 0;
}