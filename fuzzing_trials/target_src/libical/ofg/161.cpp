#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_161(const uint8_t *data, size_t size) {
    // Convert the input data to a string
    char *input = (char *)malloc(size + 1);
    if (!input) {
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(input);
    free(input);

    // Ensure that the component is not NULL
    if (component == NULL) {
        return 0;
    }

    // Initialize the iterator with the component
    icalcompiter iter = icalcomponent_begin_component(component, ICAL_ANY_COMPONENT);

    // Call the function under test
    icalcomponent *result = icalcompiter_deref(&iter);

    // Clean up
    icalcomponent_free(component);

    return 0;
}