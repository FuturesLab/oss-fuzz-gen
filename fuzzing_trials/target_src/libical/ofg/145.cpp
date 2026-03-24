#include <stdint.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_145(const uint8_t *data, size_t size) {
    // Initialize the library
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Ensure that the component is not NULL
    if (component == NULL) {
        return 0;
    }

    // Use the input data to create a comment string
    char *comment = (char *)malloc(size + 1);
    if (comment == NULL) {
        icalcomponent_free(component);
        return 0;
    }
    memcpy(comment, data, size);
    comment[size] = '\0'; // Ensure null-termination

    // Create a property using the fuzz input
    icalproperty *property = icalproperty_new_comment(comment);
    free(comment);

    // Ensure that the property is not NULL
    if (property == NULL) {
        icalcomponent_free(component);
        return 0;
    }

    // Call the function-under-test
    icalcomponent_add_property(component, property);

    // Clean up
    icalcomponent_free(component);
    // Note: The property should not be freed separately as it is now part of the component

    return 0;
}