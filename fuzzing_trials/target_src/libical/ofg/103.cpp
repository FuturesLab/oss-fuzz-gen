#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_103(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for a null-terminated string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the description string and null-terminate it
    char *description = (char *)malloc(size + 1);
    if (description == NULL) {
        return 0;
    }
    memcpy(description, data, size);
    description[size] = '\0';

    // Create a new icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        free(description);
        return 0;
    }

    // Call the function-under-test
    icalcomponent_set_description(component, description);

    // Additional operations to increase code coverage
    // Attempt to retrieve the description to ensure the function was effective
    const char *retrieved_description = icalcomponent_get_description(component);
    if (retrieved_description != NULL) {
        // Perform a simple operation to utilize the retrieved description
        size_t retrieved_length = strlen(retrieved_description);
        if (retrieved_length > 0) {
            // Just a dummy operation to ensure the description was set
            retrieved_length++;
        }
    }

    // Additional operations to increase code coverage
    // Try setting and getting other properties
    icalcomponent_set_summary(component, "Sample Summary");
    const char *summary = icalcomponent_get_summary(component);
    if (summary != NULL) {
        size_t summary_length = strlen(summary);
        if (summary_length > 0) {
            summary_length++;
        }
    }

    // Cleanup
    icalcomponent_free(component);
    free(description);

    return 0;
}