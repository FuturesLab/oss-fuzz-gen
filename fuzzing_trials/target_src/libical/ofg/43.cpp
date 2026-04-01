#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    icalcomponent *component = nullptr;

    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a temporary string from the fuzzing data
    char *temp_data = (char *)malloc(size + 1);
    if (temp_data == nullptr) {
        return 0;
    }
    memcpy(temp_data, data, size);
    temp_data[size] = '\0';

    // Parse the temporary string into an icalcomponent
    component = icalparser_parse_string(temp_data);
    free(temp_data);

    // Ensure the component is not NULL
    if (component != nullptr) {
        // Call the function-under-test
        struct icaldurationtype duration = icalcomponent_get_duration(component);

        // Clean up the component
        icalcomponent_free(component);
    }

    return 0;
}