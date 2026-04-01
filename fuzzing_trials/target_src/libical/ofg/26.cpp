#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Ensure there is enough data to read an icalcomponent_kind
    if (size < sizeof(icalcomponent_kind)) {
        return 0;
    }

    // Cast the input data to icalcomponent_kind
    icalcomponent_kind kind = *(const icalcomponent_kind *)data;

    // Call the function-under-test
    bool result = icalcomponent_kind_is_valid(kind);

    // Use the result in some way to avoid compiler optimizations
    (void)result;

    return 0;
}