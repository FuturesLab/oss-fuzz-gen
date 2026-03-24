#include <cstddef>
#include <cstdint>
#include <libical/ical.h>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    // Convert the input data to a null-terminated string
    char *input = static_cast<char *>(malloc(size + 1));
    if (input == nullptr) {
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(input);

    // Free the input string as it's no longer needed
    free(input);

    // Ensure the component is not NULL
    if (component == NULL) {
        return 0;
    }

    // Initialize the iterator with the component
    icalcompiter iter = icalcomponent_begin_component(component, ICAL_ANY_COMPONENT);

    // Call the function-under-test
    icalcomponent *next_component = icalcompiter_next(&iter);

    // Clean up
    icalcomponent_free(component);

    return 0;
}