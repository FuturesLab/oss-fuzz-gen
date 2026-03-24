#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <libical/ical.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for creating a string
    if (size == 0) {
        return 0;
    }

    // Initialize the iCalendar component
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Create a string from the input data
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        icalcomponent_free(component);
        return 0;
    }

    memcpy(inputData, data, size);
    inputData[size] = '\0';  // Null-terminate the string

    // Set a property using the input data
    icalcomponent_set_relcalid(component, inputData);

    // Call the function-under-test
    const char *relcalid = icalcomponent_get_relcalid(component);

    // Use the result in some way to avoid compiler optimizations
    if (relcalid != NULL) {
        // Print the relcalid to ensure it's being used
        printf("Relcalid: %s\n", relcalid);
    }

    // Free the allocated input data
    free(inputData);

    // Clean up
    icalcomponent_free(component);

    return 0;
}