#include <stdint.h>

extern "C" {
    #include "libical/ical.h" // Assuming the correct path for the libical headers
}

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract an icalcomponent_kind
    if (size < sizeof(icalcomponent_kind)) {
        return 0;
    }

    // Extract an icalcomponent_kind from the input data
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(data[0] % ICAL_NO_COMPONENT);

    // Call the function-under-test
    icalcomponent *component = icalcomponent_vanew(kind, nullptr);

    // Perform any necessary cleanup
    if (component != nullptr) {
        icalcomponent_free(component);
    }

    return 0;
}