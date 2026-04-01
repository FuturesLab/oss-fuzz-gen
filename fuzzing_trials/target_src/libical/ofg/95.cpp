#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_95(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated
    char *ical_data = (char *)malloc(size + 1);
    if (ical_data == NULL) {
        return 0;
    }
    memcpy(ical_data, data, size);
    ical_data[size] = '\0';

    // Parse the input data as an iCalendar string
    icalcomponent *component = icalparser_parse_string(ical_data);
    free(ical_data);

    // Ensure the component is not NULL
    if (component == NULL) {
        return 0;
    }

    // Call the function-under-test
    icalcomponent *current_component = icalcomponent_get_current_component(component);

    // Perform cleanup
    icalcomponent_free(component);

    return 0;
}