#include <libical/ical.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a valid string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *icalStr = (char *)malloc(size + 1);
    if (icalStr == NULL) {
        return 0;
    }
    memcpy(icalStr, data, size);
    icalStr[size] = '\0';

    // Parse the string into an icalcomponent
    icalcomponent *comp = icalparser_parse_string(icalStr);
    if (comp != NULL) {
        // Call the function-under-test
        struct icaltimetype dtstamp = icalcomponent_get_dtstamp(comp);

        // Clean up
        icalcomponent_free(comp);
    }

    free(icalStr);
    return 0;
}