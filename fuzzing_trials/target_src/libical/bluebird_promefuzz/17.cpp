#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "libical/ical.h"
#include <cstdlib>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    // Prepare a dummy file for operations that require a file
    std::ofstream dummyFile("./dummy_file");
    if (!dummyFile.is_open()) {
        return 0;
    }
    dummyFile.write(reinterpret_cast<const char*>(Data), Size);
    dummyFile.close();

    // Initialize a component and properties for testing
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalproperty *property = icalproperty_new_summary("Test Summary");
    icalcomponent_add_property(component, property);

    // Test icalcomponent_begin_property
    icalpropiter iter = icalcomponent_begin_property(component, ICAL_SUMMARY_PROPERTY);

    // Test icalpropiter_deref
    icalproperty *currentProperty = icalpropiter_deref(&iter);
    if (currentProperty) {
        const char *summary = icalproperty_get_summary(currentProperty);
    }

    // Test icalpropiter_next
    while ((currentProperty = icalpropiter_next(&iter)) != nullptr) {
        const char *summary = icalproperty_get_summary(currentProperty);
    }

    // Test icalcomponent_get_next_property
    currentProperty = icalcomponent_get_next_property(component, ICAL_SUMMARY_PROPERTY);
    if (currentProperty) {
        const char *summary = icalproperty_get_summary(currentProperty);
    }

    // Test icalcomponent_get_current_property
    currentProperty = icalcomponent_get_current_property(component);
    if (currentProperty) {
        const char *summary = icalproperty_get_summary(currentProperty);
    }

    // Test icalcomponent_get_first_property
    currentProperty = icalcomponent_get_first_property(component, ICAL_SUMMARY_PROPERTY);
    if (currentProperty) {
        const char *summary = icalproperty_get_summary(currentProperty);
    }

    // Cleanup
    icalcomponent_free(component);

    return 0;
}