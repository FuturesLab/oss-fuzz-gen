#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_vpoll();

    // Normally, you would do something with the component here,
    // like manipulating it or checking its properties.

    // Clean up
    if (component != NULL) {
        icalcomponent_free(component);
    }

    return 0;
}