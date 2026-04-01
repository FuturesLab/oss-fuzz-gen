#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
    // Ensure there is enough data to read an icalcomponent_kind value
    if (size < sizeof(icalcomponent_kind)) {
        return 0;
    }

    // Extract icalcomponent_kind from the input data
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(data[0]);

    // Call the function-under-test
    icalcomponent *component = icalcomponent_new(kind);

    // Clean up
    if (component != NULL) {
        icalcomponent_free(component);
    }

    return 0;
}