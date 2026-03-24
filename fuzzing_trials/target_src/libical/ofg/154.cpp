#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include string.h for memcpy

extern "C" {
    #include <libical/icalcomponent.h> // Include the correct header for libical
    #include <libical/icalparser.h>    // Include the parser header
}

extern "C" int LLVMFuzzerTestOneInput_154(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Create a temporary icalcomponent from the input data
    char *ical_str = (char *)malloc(size + 1);
    if (ical_str == NULL) {
        return 0;
    }
    memcpy(ical_str, data, size);
    ical_str[size] = '\0';

    // Parse the ical string into an icalcomponent
    icalcomponent *comp = icalparser_parse_string(ical_str);
    free(ical_str);

    if (comp != NULL) {
        // Call the function-under-test
        icalcomponent_kind kind = icalcomponent_isa(comp);

        // Clean up the icalcomponent
        icalcomponent_free(comp);
    }

    return 0;
}