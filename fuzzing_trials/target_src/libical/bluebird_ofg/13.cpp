#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern "C" {
    #include "libical/ical.h"
    #include "/src/libical/src/libical/icalcomponent.h" // Include the header for icalcomponent functions
}

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    // Initialize an icalcomponent object.
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);

    // Ensure that the data is non-null and has a valid size.
    if (data != nullptr && size > 0) {
        // Create a string from the input data.
        char *inputData = (char *)malloc(size + 1);
        if (inputData != nullptr) {
            memcpy(inputData, data, size);
            inputData[size] = '\0'; // Null-terminate the string.

            // Add a comment to the icalcomponent using the input data.
            icalproperty *commentProperty = icalproperty_new_comment(inputData);
            icalcomponent_add_property(component, commentProperty);

            // Free the allocated memory for inputData.
            free(inputData);
        }
    }

    // Call the function-under-test.
    // Instead of simply getting the comment, let's iterate over properties to ensure interaction.
    for (icalproperty *prop = icalcomponent_get_first_property(component, ICAL_ANY_PROPERTY);
         prop != nullptr;
         prop = icalcomponent_get_next_property(component, ICAL_ANY_PROPERTY)) {
        // Use the property in some way to avoid compiler optimizations removing it.
        const char *propName = icalproperty_get_property_name(prop);
        if (propName != nullptr) {
            // For example, just print it (in a real fuzzing scenario, you might not print).
            printf("Property: %s\n", propName);
        }
    }

    // Clean up the icalcomponent.
    icalcomponent_free(component);

    return 0;
}