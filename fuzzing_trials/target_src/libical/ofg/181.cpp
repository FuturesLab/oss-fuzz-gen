#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/icalcomponent.h>
}

extern "C" int LLVMFuzzerTestOneInput_181(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a comment string
    if (size < 1) {
        return 0;
    }

    // Create an icalcomponent object
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Convert the data to a null-terminated string for the comment
    char *comment = (char *)malloc(size + 1);
    if (comment == NULL) {
        icalcomponent_free(component);
        return 0;
    }
    memcpy(comment, data, size);
    comment[size] = '\0';

    // Call the function-under-test
    icalcomponent_set_comment(component, comment);

    // Clean up
    free(comment);
    icalcomponent_free(component);

    return 0;
}