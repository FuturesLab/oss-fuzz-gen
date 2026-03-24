#include <cstdint>
#include <cstdlib>
#include <cstring> // Include this header for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_149(const uint8_t *data, size_t size) {
    // Initialize the library
    icalcomponent *component = nullptr;

    // Create a dummy icalcomponent
    component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == nullptr) {
        return 0; // If creation fails, return early
    }

    // Create a dummy UID string from the input data
    char uid[256] = {0}; // Ensure it's large enough and null-terminated
    size_t copy_size = size < 255 ? size : 255; // Limit size to prevent overflow
    memcpy(uid, data, copy_size);
    uid[copy_size] = '\0'; // Ensure null termination

    // Set the UID on the component
    icalcomponent_set_uid(component, uid);

    // Call the function-under-test
    const char *retrieved_uid = icalcomponent_get_uid(component);

    // Check if the retrieved UID matches the set UID
    if (retrieved_uid && strcmp(retrieved_uid, uid) != 0) {
        // If they don't match, there might be a bug
        abort();
    }

    // Clean up
    icalcomponent_free(component);

    return 0;
}