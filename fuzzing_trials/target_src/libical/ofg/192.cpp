#include <cstdint> // Include for uint8_t
#include <cstdlib> // Include for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_192(const uint8_t *data, size_t size) {
    // Initialize the fuzzing environment
    // The function icalcomponent_new_xvote does not require any input parameters

    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_xvote();

    // Perform cleanup if necessary
    if (component != NULL) {
        icalcomponent_free(component);
    }

    return 0;
}