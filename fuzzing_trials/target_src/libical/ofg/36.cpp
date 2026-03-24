#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/icalcomponent.h>
}

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a null-terminated string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *x_name = (char *)malloc(size + 1);
    if (x_name == NULL) {
        return 0;
    }
    memcpy(x_name, data, size);
    x_name[size] = '\0';

    // Initialize an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        free(x_name);
        return 0;
    }

    // Call the function under test
    icalcomponent_set_x_name(component, x_name);

    // Clean up
    icalcomponent_free(component);
    free(x_name);

    return 0;
}