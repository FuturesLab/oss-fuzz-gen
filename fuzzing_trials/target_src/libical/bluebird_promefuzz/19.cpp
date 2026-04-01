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
#include "libical/ical.h"

static icalcomponent* create_dummy_component() {
    icalcomponent* comp = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    return comp;
}

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Create a dummy component
    icalcomponent* comp = create_dummy_component();
    if (!comp) return 0;

    // Use data to create strings for location and comment
    std::string location(reinterpret_cast<const char*>(Data), Size);
    std::string comment(reinterpret_cast<const char*>(Data), Size);

    // Test icalcomponent_set_location
    icalcomponent_set_location(comp, location.c_str());

    // Test icalcomponent_get_location
    const char* loc = icalcomponent_get_location(comp);
    if (loc) {
        std::cout << "Location: " << loc << std::endl;
    }

    // Test icalcomponent_set_comment
    icalcomponent_set_comment(comp, comment.c_str());

    // Test icalcomponent_get_comment
    const char* com = icalcomponent_get_comment(comp);
    if (com) {
        std::cout << "Comment: " << com << std::endl;
    }

    // Test icalcomponent_check_restrictions
    bool isValid = icalcomponent_check_restrictions(comp);
    std::cout << "Component is " << (isValid ? "valid" : "invalid") << std::endl;

    // Test icalcomponent_get_component_name
    const char* name = icalcomponent_get_component_name(comp);
    if (name) {
        std::cout << "Component Name: " << name << std::endl;
    }

    // Clean up
    icalcomponent_free(comp);

    return 0;
}