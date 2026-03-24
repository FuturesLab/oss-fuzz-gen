#include <stdint.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_106(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for our needs
    if (size < 2) {
        return 0;
    }

    // Initialize an icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Use the first byte of data to determine the method
    icalproperty_method method = static_cast<icalproperty_method>(data[0] % ICAL_METHOD_NONE);

    // Call the function-under-test
    icalcomponent_set_method(component, method);

    // Use the remaining data to set a property, ensuring the input is not null
    char *summary = strndup(reinterpret_cast<const char *>(data + 1), size - 1);
    if (summary != NULL) {
        icalproperty *prop = icalproperty_new_summary(summary);
        if (prop != NULL) {
            icalcomponent_add_property(component, prop);
        }
        free(summary);
    }

    // Clean up
    icalcomponent_free(component);

    return 0;
}