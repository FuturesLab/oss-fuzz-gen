#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_141(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient to create a valid string
    if (size < 1) {
        return 0;
    }

    // Initialize the icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *timezone_id = (char *)malloc(size + 1);
    if (timezone_id == NULL) {
        icalcomponent_free(component);
        return 0;
    }
    memcpy(timezone_id, data, size);
    timezone_id[size] = '\0';

    // Call the function-under-test
    icaltimezone *timezone = icalcomponent_get_timezone(component, timezone_id);

    // Clean up
    free(timezone_id);
    icalcomponent_free(component);

    return 0;
}