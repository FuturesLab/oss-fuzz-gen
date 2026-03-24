#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_102(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_xdaylight();

    // Clean up if the component is not NULL
    if (component != NULL) {
        icalcomponent_free(component);
    }

    return 0;
}