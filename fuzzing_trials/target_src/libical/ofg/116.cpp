#include <cstdint> // Include standard library for uint8_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_116(const uint8_t *data, size_t size) {
    // Initialize a dummy icalcomponent and icalproperty for testing
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalproperty *property = icalproperty_new_summary("Test Summary");
    icalcomponent_add_property(component, property);

    // Initialize an icalproperty and assign it to the iterator
    icalproperty *result_property = nullptr;
    icalproperty *prop_iter = icalcomponent_get_first_property(component, ICAL_ANY_PROPERTY);

    while (prop_iter != nullptr) {
        // Call the function-under-test
        result_property = prop_iter;
        prop_iter = icalcomponent_get_next_property(component, ICAL_ANY_PROPERTY);
    }

    // Clean up
    icalcomponent_free(component);

    return 0;
}