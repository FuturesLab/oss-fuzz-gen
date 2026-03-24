#include <cstdint> // Include for uint8_t
#include <cstdlib> // Include for malloc and free
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_143(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create a valid icalcomponent
    if (size < 1) {
        return 0;
    }

    // Initialize an icalcomponent from the input data
    char *input_data = (char *)malloc(size + 1);
    if (input_data == NULL) {
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0';

    icalcomponent *component = icalparser_parse_string(input_data);
    free(input_data);

    if (component == NULL) {
        return 0;
    }

    // Iterate over all possible icalcomponent_kind values
    for (int kind = ICAL_NO_COMPONENT; kind <= ICAL_XROOT_COMPONENT; ++kind) {
        icalcomponent_kind component_kind = static_cast<icalcomponent_kind>(kind);
        
        // Call the function-under-test
        icalcomponent *first_component = icalcomponent_get_first_component(component, component_kind);
        
        // Optionally, you can perform additional operations or checks on first_component
        // For example, you could print its kind or check for null
        if (first_component != NULL) {
            icalcomponent_kind found_kind = icalcomponent_isa(first_component);
            // Do something with found_kind if needed
        }
    }

    // Clean up
    icalcomponent_free(component);

    return 0;
}