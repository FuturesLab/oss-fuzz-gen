#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for our needs
    if (size < 1) {
        return 0;
    }

    // Create a new icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Extract a status value from the input data
    icalproperty_status status = 
        static_cast<icalproperty_status>(data[0] % 7); // Assuming there are 7 possible statuses

    // Create an icalproperty for status and add it to the component
    icalproperty *status_property = icalproperty_new_status(status);
    icalcomponent_add_property(component, status_property);

    // Serialize the component to a string to ensure it is processed
    char *component_str = icalcomponent_as_ical_string(component);

    // Check if the component string is not null and has some content
    if (component_str != nullptr && strlen(component_str) > 0) {
        // Optionally print or log the component string for debugging
        // printf("Component: %s\n", component_str);
    }

    // Clean up
    icalcomponent_free(component);

    return 0;
}