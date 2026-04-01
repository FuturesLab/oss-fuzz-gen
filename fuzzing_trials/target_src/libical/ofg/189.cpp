#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_189(const uint8_t *data, size_t size) {
    // Create a memory context for the fuzzing session
    icalproperty *property = nullptr;
    icalcomponent *component = nullptr;

    // Ensure that the input size is sufficient to create a valid string for the property
    if (size < 2) {
        return 0;
    }

    // Allocate memory for the property and component strings
    char *property_str = static_cast<char *>(malloc(size / 2 + 1));
    char *component_str = static_cast<char *>(malloc(size / 2 + 1));

    // Copy the data into the strings and null-terminate them
    memcpy(property_str, data, size / 2);
    property_str[size / 2] = '\0';

    memcpy(component_str, data + size / 2, size / 2);
    component_str[size / 2] = '\0';

    // Create the icalproperty and icalcomponent from the strings
    property = icalproperty_new_from_string(property_str);
    component = icalcomponent_new_from_string(component_str);

    // Check if the property and component were created successfully
    if (property != nullptr && component != nullptr) {
        // Call the function-under-test
        struct icaltimetype result = icalproperty_get_datetime_with_component(property, component);

        // Use the result in some way to prevent optimization out
        (void)result;
    }

    // Clean up
    if (property != nullptr) {
        icalproperty_free(property);
    }
    if (component != nullptr) {
        icalcomponent_free(component);
    }
    free(property_str);
    free(component_str);

    return 0;
}