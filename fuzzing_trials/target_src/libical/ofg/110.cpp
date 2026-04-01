#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_110(const uint8_t *data, size_t size) {
    // Ensure there's enough data to create a valid icalcomponent
    if (size < 1) {
        return 0;
    }

    // Create an icalcomponent from the input data
    // Assuming the data is a string representation of an iCalendar component
    char *ical_str = (char *)malloc(size + 1);
    if (ical_str == NULL) {
        return 0;
    }
    memcpy(ical_str, data, size);
    ical_str[size] = '\0';

    icalcomponent *component = icalparser_parse_string(ical_str);
    free(ical_str);

    if (component == NULL) {
        return 0;
    }

    // Call the function-under-test
    const char *x_name = icalcomponent_get_x_name(component);

    // Print the result for debugging purposes (optional)
    if (x_name != NULL) {
        printf("X-Name: %s\n", x_name);
    }

    // Clean up
    icalcomponent_free(component);

    return 0;
}