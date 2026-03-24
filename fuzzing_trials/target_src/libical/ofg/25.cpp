#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>  // Include this to resolve the 'size_t' type

// Assuming the necessary declarations are available in the following extern "C" block
extern "C" {
    // Declare the type icalcomponent_kind
    typedef enum icalcomponent_kind {
        ICAL_NO_COMPONENT = 0,
        ICAL_VEVENT_COMPONENT,
        ICAL_VTODO_COMPONENT,
        // Add other kinds as necessary
    } icalcomponent_kind;

    // Declare the function icalcomponent_kind_is_valid
    bool icalcomponent_kind_is_valid(const icalcomponent_kind kind);
}

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to extract an icalcomponent_kind value
    if (size < sizeof(icalcomponent_kind)) {
        return 0;
    }

    // Interpret the input data as an icalcomponent_kind
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(data[0]);

    // Call the function-under-test
    bool result = icalcomponent_kind_is_valid(kind);

    // Use the result in some way to avoid compiler optimizations
    if (result) {
        // Do something if the kind is valid (no-op here)
    }

    return 0;
}