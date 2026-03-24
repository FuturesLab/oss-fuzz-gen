// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_get_description at icalcomponent.c:1897:13 in icalcomponent.h
// icalcomponent_as_ical_string at icalcomponent.c:215:7 in icalcomponent.h
// icalcomponent_set_relcalid at icalcomponent.c:2573:6 in icalcomponent.h
// icalcomponent_get_component_name at icalcomponent.c:344:13 in icalcomponent.h
// icalcomponent_new_valarm at icalcomponent.c:2045:16 in icalcomponent.h
// icalcomponent_set_summary at icalcomponent.c:1734:6 in icalcomponent.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <cstring>
#include "ical.h"

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Create a new VALARM component
    icalcomponent *component = icalcomponent_new_valarm();
    if (!component) {
        return 0;
    }

    // Use part of the input data for setting properties
    size_t halfSize = Size / 2;
    std::string description(reinterpret_cast<const char *>(Data), halfSize);
    std::string summary(reinterpret_cast<const char *>(Data + halfSize), Size - halfSize);

    // Set the description and summary using input data
    icalcomponent_set_summary(component, summary.c_str());
    icalcomponent_set_relcalid(component, description.c_str());

    // Convert component to string
    char *icalString = icalcomponent_as_ical_string(component);
    if (icalString) {
        // Simulate usage of the string
        std::cout << "iCal String: " << icalString << std::endl;
    }

    // Get the component's description
    const char *compDescription = icalcomponent_get_description(component);
    if (compDescription) {
        std::cout << "Description: " << compDescription << std::endl;
    }

    // Get the component's name
    const char *componentName = icalcomponent_get_component_name(component);
    if (componentName) {
        std::cout << "Component Name: " << componentName << std::endl;
    }

    // Cleanup
    icalcomponent_free(component);

    return 0;
}