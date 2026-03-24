#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_84(const uint8_t *data, size_t size) {
    // Ensure that size is large enough to create a valid string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *icalStr = (char *)malloc(size + 1);
    if (icalStr == nullptr) {
        return 0;
    }
    memcpy(icalStr, data, size);
    icalStr[size] = '\0';

    // Parse the string into an icalcomponent
    icalcomponent *component = icalparser_parse_string(icalStr);
    if (component != nullptr) {
        // Call the function-under-test
        icalproperty_method method = icalcomponent_get_method(component);

        // Clean up
        icalcomponent_free(component);
    }

    free(icalStr);
    return 0;
}