#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
    // Initialize an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Ensure the data is null-terminated for use as a string
    char *summary = (char *)malloc(size + 1);
    if (summary == NULL) {
        icalcomponent_free(component);
        return 0;
    }
    memcpy(summary, data, size);
    summary[size] = '\0';

    // Call the function-under-test
    icalcomponent_set_summary(component, summary);

    // Clean up
    free(summary);
    icalcomponent_free(component);

    return 0;
}