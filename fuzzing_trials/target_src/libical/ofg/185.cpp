#include <stddef.h>
#include <stdint.h>
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_185(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Initialize the icaltimetype structures
    struct icaltimetype start_time;
    struct icaltimetype end_time;

    // Ensure that the data size is sufficient to populate the icaltimetype structures
    if (size >= sizeof(struct icaltimetype) * 2) {
        // Populate start_time and end_time with data
        memcpy(&start_time, data, sizeof(struct icaltimetype));
        memcpy(&end_time, data + sizeof(struct icaltimetype), sizeof(struct icaltimetype));
    } else {
        // Use default values if data size is insufficient
        start_time = icaltime_null_time();
        end_time = icaltime_null_time();
    }

    // Call the function-under-test
    bool result = icalproperty_recurrence_is_excluded(component, &start_time, &end_time);

    // Clean up
    icalcomponent_free(component);

    return 0;
}