#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_129(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *participant = icalcomponent_new_participant();

    // Check if the participant was created successfully
    if (participant != NULL) {
        // Perform operations on the participant if needed
        // For example, you can add properties, etc.

        // Free the participant after use
        icalcomponent_free(participant);
    }

    return 0;
}