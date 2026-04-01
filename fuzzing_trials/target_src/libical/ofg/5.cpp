#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/icalcomponent.h>
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    // Ensure that the data is null-terminated to be used as a C-string
    char *relcalid = (char *)malloc(size + 1);
    if (!relcalid) {
        return 0; // Memory allocation failed
    }
    memcpy(relcalid, data, size);
    relcalid[size] = '\0';

    // Create a dummy icalcomponent object
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        free(relcalid);
        return 0; // Failed to create icalcomponent
    }

    // Call the function-under-test
    icalcomponent_set_relcalid(component, relcalid);

    // Clean up
    icalcomponent_free(component);
    free(relcalid);

    return 0;
}