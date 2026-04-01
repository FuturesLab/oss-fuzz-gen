#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a valid string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *inputString = static_cast<char *>(malloc(size + 1));
    if (inputString == nullptr) {
        return 0;
    }
    memcpy(inputString, data, size);
    inputString[size] = '\0';

    // Parse the input string into an icalcomponent
    icalcomponent *component = icalparser_parse_string(inputString);
    free(inputString);

    // Ensure the component is not NULL
    if (component != nullptr) {
        // Call the function-under-test
        char *icalString = icalcomponent_as_ical_string(component);

        // Free the string returned by the function-under-test
        if (icalString != nullptr) {
            free(icalString);
        }

        // Clean up the icalcomponent
        icalcomponent_free(component);
    }

    return 0;
}