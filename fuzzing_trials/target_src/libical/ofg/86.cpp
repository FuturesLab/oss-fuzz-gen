#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_86(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a valid icalcomponent
    if (size < 1) {
        return 0;
    }

    // Create an icalcomponent from the input data
    char *ical_str = (char *)malloc(size + 1);
    if (ical_str == NULL) {
        return 0;
    }
    memcpy(ical_str, data, size);
    ical_str[size] = '\0';  // Null-terminate the string

    icalcomponent *component = icalparser_parse_string(ical_str);
    free(ical_str);

    if (component != NULL) {
        // Call the function-under-test
        icalproperty *property = icalcomponent_get_current_property(component);

        // Perform any additional operations if needed
        // (e.g., iterate over properties, check values, etc.)

        // Clean up
        icalcomponent_free(component);
    }

    return 0;
}