#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_99(const uint8_t *data, size_t size) {
    // Initialize variables for fuzzing
    icalcomponent *comp = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalcomponent_kind kind = ICAL_VEVENT_COMPONENT;

    // Ensure the data is not empty
    if (size > 0) {
        // Create a temporary buffer to hold the input data
        char *buffer = (char *)malloc(size + 1);
        if (buffer == NULL) {
            icalcomponent_free(comp);
            return 0;
        }

        // Copy the data into the buffer and null-terminate it
        memcpy(buffer, data, size);
        buffer[size] = '\0';

        // Attempt to parse the input data as an icalcomponent
        icalcomponent *parsed_comp = icalparser_parse_string(buffer);
        if (parsed_comp != NULL) {
            // If parsing was successful, use the parsed component
            icalcomponent_free(comp);
            comp = parsed_comp;
        }

        free(buffer);
    }

    // Fuzz the function-under-test
    icalcompiter iter = icalcomponent_end_component(comp, kind);

    // Clean up
    icalcomponent_free(comp);

    return 0;
}