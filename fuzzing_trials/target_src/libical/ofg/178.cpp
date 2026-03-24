#include <cstdint>
#include <cstddef>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_178(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create a string from the input data
    char *input = new char[size + 1];
    memcpy(input, data, size);
    input[size] = '\0';

    // Parse the input data as an iCalendar component
    icalcomponent *component = icalparser_parse_string(input);

    // Clean up
    delete[] input;

    if (component != NULL) {
        // Perform some operations on the component to increase coverage
        icalcomponent *clone = icalcomponent_clone(component);
        if (clone != NULL) {
            icalcomponent_free(clone);
        }
        icalcomponent_free(component);
    }

    return 0;
}