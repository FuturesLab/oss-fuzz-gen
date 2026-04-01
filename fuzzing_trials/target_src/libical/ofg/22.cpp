#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a meaningful string
    if (size == 0) return 0;

    // Create a null-terminated string from the input data
    char *inputString = (char *)malloc(size + 1);
    if (inputString == NULL) return 0;
    memcpy(inputString, data, size);
    inputString[size] = '\0';

    // Parse the input string to create an icalcomponent
    icalcomponent *component = icalparser_parse_string(inputString);

    // Call the function-under-test if the component is successfully created
    if (component != NULL) {
        char *icalString = icalcomponent_as_ical_string(component);
        // Free the string returned by icalcomponent_as_ical_string
        if (icalString != NULL) {
            free(icalString);
        }
        // Free the icalcomponent
        icalcomponent_free(component);
    }

    // Free the allocated input string
    free(inputString);

    return 0;
}