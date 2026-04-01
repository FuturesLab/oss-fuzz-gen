#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_98(const uint8_t *data, size_t size) {
    // Initialize a dummy icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    
    // Ensure the data size is sufficient to extract a valid icalcomponent_kind
    if (size < sizeof(icalcomponent_kind)) {
        icalcomponent_free(component);
        return 0;
    }

    // Extract icalcomponent_kind from the data
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(data[0] % ICAL_NO_COMPONENT);

    // Call the function under test
    icalcompiter iterator = icalcomponent_end_component(component, kind);

    // Cleanup
    icalcomponent_free(component);

    return 0;
}