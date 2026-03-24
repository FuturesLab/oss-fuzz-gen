#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h> // Include for malloc and free

extern "C" {
    #include <libical/ical.h> // Correct path for the ical header
}

extern "C" int LLVMFuzzerTestOneInput_180(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a null-terminated string
    if (size == 0) {
        return 0;
    }

    // Create an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *comment = (char *)malloc(size + 1);
    if (comment == NULL) {
        icalcomponent_free(component);
        return 0;
    }
    memcpy(comment, data, size);
    comment[size] = '\0';

    // Call the function under test
    // Ensure the comment is not empty to increase the chance of meaningful execution
    if (strlen(comment) > 0) {
        icalcomponent_set_comment(component, comment);
    }

    // Clean up
    free(comment);
    icalcomponent_free(component);

    return 0;
}