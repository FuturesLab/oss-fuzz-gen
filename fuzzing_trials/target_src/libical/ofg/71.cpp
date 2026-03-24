#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_71(const uint8_t *data, size_t size) {
    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to hold the input data
    char *buffer = static_cast<char *>(malloc(size + 1));
    if (buffer == NULL) {
        return 0;
    }

    // Copy the input data to the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Parse the buffer into an icalcomponent
    icalcomponent *component = icalparser_parse_string(buffer);

    // Check if the component was successfully created
    if (component != NULL) {
        // Call the function-under-test
        char *ical_string = icalcomponent_as_ical_string_r(component);

        // Free the returned string if it's not NULL
        if (ical_string != NULL) {
            free(ical_string);
        }

        // Free the icalcomponent
        icalcomponent_free(component);
    }

    // Free the temporary buffer
    free(buffer);

    return 0;
}