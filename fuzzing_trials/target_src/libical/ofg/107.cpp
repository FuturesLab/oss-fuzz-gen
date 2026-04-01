#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_107(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract a method
    if (size < sizeof(icalproperty_method)) {
        return 0;
    }

    // Create a new icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Extract a method from the data
    icalproperty_method method = static_cast<icalproperty_method>(data[0] % ICAL_METHOD_NONE);

    // Call the function-under-test
    icalcomponent_set_method(component, method);

    // Clean up
    icalcomponent_free(component);

    return 0;
}