#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>
#include <cstring> // For memcpy

extern "C" {
    // Define a callback function to be used with icalcomponent_foreach_recurrence
    void recurrence_callback(icalcomponent *comp, const struct icaltime_span *span, void *data) {
        // This is a simple callback that does nothing.
        // You can extend it to perform operations on each recurrence.
    }
}

extern "C" int LLVMFuzzerTestOneInput_188(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent with some default values
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Define start and end times for the recurrence
    struct icaltimetype start_time = icaltime_from_string("20230101T000000Z");
    struct icaltimetype end_time = icaltime_from_string("20231231T235959Z");

    // Ensure the data is not NULL and size is sufficient for a simple operation
    if (size > 0) {
        // Create a temporary buffer to hold the data for the icalcomponent
        char *temp_data = new char[size + 1];
        memcpy(temp_data, data, size);
        temp_data[size] = '\0'; // Null-terminate the buffer

        // Parse the data into an icalproperty and add it to the component
        icalproperty *prop = icalproperty_new_from_string(temp_data);
        if (prop != nullptr) {
            icalcomponent_add_property(component, prop);
        }

        // Call the function under test
        icalcomponent_foreach_recurrence(component, start_time, end_time, recurrence_callback, nullptr);

        // Clean up
        delete[] temp_data;
    }

    icalcomponent_free(component);

    return 0;
}