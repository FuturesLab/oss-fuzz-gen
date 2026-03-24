#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for a null-terminated string and meaningful UID
    if (size < 5) { // Arbitrary minimum size for a meaningful UID
        return 0;
    }

    // Allocate memory for the UID string and ensure null-termination
    char *uid = (char *)malloc(size + 1);
    if (uid == NULL) {
        return 0;
    }
    memcpy(uid, data, size);
    uid[size] = '\0';

    // Create a new icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        free(uid);
        return 0;
    }

    // Call the function-under-test
    icalcomponent_set_uid(component, uid);

    // Additional operations to ensure code coverage
    // For example, retrieve the UID and perform a check
    const char *retrieved_uid = icalcomponent_get_uid(component);
    if (retrieved_uid != NULL && strcmp(retrieved_uid, uid) == 0) {
        // UID was set and retrieved successfully
    }

    // Clean up
    icalcomponent_free(component);
    free(uid);

    return 0;
}