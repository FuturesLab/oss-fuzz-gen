#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
    // Ensure the data is not empty to avoid unnecessary processing
    if (size == 0) {
        return 0;
    }

    // Create a new icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Copy the data to a null-terminated string
    char *description = (char *)malloc(size + 1);
    if (description == NULL) {
        icalcomponent_free(component);
        return 0;
    }
    memcpy(description, data, size);
    description[size] = '\0';

    // Call the function-under-test
    icalcomponent_set_description(component, description);

    // Additional operation to ensure code coverage
    const char *retrieved_description = icalcomponent_get_description(component);
    if (retrieved_description != NULL) {
        // Process retrieved description to ensure it's being used
        size_t retrieved_length = strlen(retrieved_description);
        if (retrieved_length > 0) {
            // Perform some operation, e.g., logging or further manipulation
            // For fuzzing purposes, we can attempt to parse it back or perform other operations
            char *parsed_description = strdup(retrieved_description);
            if (parsed_description) {
                // Simulate further processing
                free(parsed_description);
            }
        }
    }

    // Perform additional operations on the component to increase coverage
    icalcomponent_kind kind = icalcomponent_isa(component);
    if (kind == ICAL_VEVENT_COMPONENT) {
        // Further manipulate the component
        icalcomponent_set_summary(component, "Sample Summary");

        // Try adding an attendee to increase code coverage
        icalproperty *attendee = icalproperty_new_attendee("mailto:example@example.com");
        if (attendee) {
            icalcomponent_add_property(component, attendee);
        }
    }

    // Additional operations to further increase coverage
    // Attempt to serialize the component to a string
    char *component_str = icalcomponent_as_ical_string(component);
    if (component_str) {
        // Simulate processing of the serialized string
        size_t component_str_length = strlen(component_str);
        if (component_str_length > 0) {
            char *processed_str = strdup(component_str);
            if (processed_str) {
                // Simulate further processing
                free(processed_str);
            }
        }
    }

    // Clean up
    free(description);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_free to icalcomponent_get_x_name

        const char* ret_icalcomponent_get_x_name_aaren = icalcomponent_get_x_name(component);
        if (ret_icalcomponent_get_x_name_aaren == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

    icalcomponent_free(component);

    return 0;
}