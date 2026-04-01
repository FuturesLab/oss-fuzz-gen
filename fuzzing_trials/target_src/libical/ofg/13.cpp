#include <cstdint>
#include <cstddef>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_xstandard();

    // Ensure we clean up by freeing the allocated component
    if (component != NULL) {
        icalcomponent_free(component);
    }

    return 0;
}