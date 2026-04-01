#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_179(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to safely use it as a string
    char *null_terminated_data = new char[size + 1];
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Attempt to parse the input data as an iCalendar component
    icalcomponent *component = icalparser_parse_string(null_terminated_data);

    // Perform operations on the created component if needed
    if (component != NULL) {
        // Optionally, perform further operations or checks on the component

        // Free the component after use
        icalcomponent_free(component);
    }

    // Clean up the null-terminated data
    delete[] null_terminated_data;

    return 0;
}