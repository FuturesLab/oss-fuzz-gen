#include <cstdint>
#include <cstdlib>
#include <cstring> // Include the header for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a valid string
    if (size == 0) return 0;

    // Create a null-terminated string from the input data
    char *ical_data = static_cast<char *>(malloc(size + 1));
    if (!ical_data) return 0;
    memcpy(ical_data, data, size);
    ical_data[size] = '\0';

    // Parse the string into an icalcomponent
    icalcomponent *component = icalparser_parse_string(ical_data);

    // Free the allocated string memory
    free(ical_data);

    if (component != NULL) {
        // Try different property kinds
        icalproperty_kind kinds[] = {
            ICAL_ANY_PROPERTY,
            ICAL_NO_PROPERTY,
            ICAL_X_PROPERTY,
            ICAL_ATTACH_PROPERTY,
            ICAL_SUMMARY_PROPERTY
        };

        // Call the function-under-test with different property kinds
        for (size_t i = 0; i < sizeof(kinds) / sizeof(kinds[0]); ++i) {
            int count = icalcomponent_count_properties(component, kinds[i]);
            (void)count; // Suppress unused variable warning
        }

        // Free the component
        icalcomponent_free(component);
    }

    return 0;
}