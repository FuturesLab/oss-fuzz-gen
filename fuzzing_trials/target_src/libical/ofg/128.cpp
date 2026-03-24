#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_128(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *participant = icalcomponent_new_participant();

    // Normally, you would interact with the `participant` object here.
    // For fuzzing purposes, you might want to perform operations that
    // could expose vulnerabilities, like modifying or querying the component.
    // However, since the function does not take any input parameters,
    // there's not much we can do with `data` and `size` directly.

    // Clean up the created component to avoid memory leaks
    if (participant != NULL) {
        icalcomponent_free(participant);
    }

    return 0;
}