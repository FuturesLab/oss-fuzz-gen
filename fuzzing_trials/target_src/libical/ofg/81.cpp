#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_81(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_xavailable();

    // Perform any additional operations on the component if necessary
    // For this fuzzing harness, we will just free the component

    if (component != NULL) {
        icalcomponent_free(component);
    }

    return 0;
}