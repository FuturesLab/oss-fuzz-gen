#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h> // For malloc and free
#include <string.h> // For memcpy

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_190(const uint8_t *data, size_t size) {
    // Initialize necessary variables
    icalproperty *property = nullptr;
    icalcomponent *component = nullptr;
    struct icaltimetype datetime;

    // Ensure size is sufficient to create a valid string
    if (size < 1) {
        return 0;
    }

    // Create a string from the data
    char *ical_string = (char *)malloc(size + 1);
    if (ical_string == nullptr) {
        return 0;
    }
    memcpy(ical_string, data, size);
    ical_string[size] = '\0';

    // Parse the string to create an icalcomponent
    component = icalparser_parse_string(ical_string);
    if (component != nullptr) {
        // Create a dummy icalproperty for testing
        property = icalproperty_new(ICAL_DTSTART_PROPERTY);
        if (property != nullptr) {
            // Call the function-under-test
            datetime = icalproperty_get_datetime_with_component(property, component);

            // Clean up the property
            icalproperty_free(property);
        }

        // Clean up the component
        icalcomponent_free(component);
    }

    // Free the allocated string
    free(ical_string);

    return 0;
}