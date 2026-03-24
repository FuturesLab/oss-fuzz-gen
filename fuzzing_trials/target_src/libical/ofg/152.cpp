#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_152(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract an icalcomponent_kind
    if (size < sizeof(icalcomponent_kind)) {
        return 0;
    }

    // Extract icalcomponent_kind from the input data
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(data[0]);

    // Call the function-under-test
    icalcomponent *component = icalcomponent_vanew(kind, nullptr);

    // Clean up the created component
    if (component != nullptr) {
        icalcomponent_free(component);
    }

    return 0;
}