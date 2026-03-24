// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_get_location at icalcomponent.c:1932:13 in icalcomponent.h
// icalcomponent_set_location at icalcomponent.c:1920:6 in icalcomponent.h
// icalcomponent_get_component_name at icalcomponent.c:344:13 in icalcomponent.h
// icalcomponent_get_uid at icalcomponent.c:1816:13 in icalcomponent.h
// icalcomponent_set_x_name at icalcomponent.c:324:6 in icalcomponent.h
// icalcomponent_get_x_name at icalcomponent.c:337:13 in icalcomponent.h
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
#include <string>
#include <cstring>
#include "ical.h"

static void setLocation(icalcomponent *comp, const char *location) {
    icalcomponent_set_location(comp, location);
}

static const char* getUID(icalcomponent *comp) {
    return icalcomponent_get_uid(comp);
}

static const char* getXName(const icalcomponent *comp) {
    return icalcomponent_get_x_name(comp);
}

static void setXName(icalcomponent *comp, const char *x_name) {
    icalcomponent_set_x_name(comp, x_name);
}

static const char* getComponentName(const icalcomponent *comp) {
    return icalcomponent_get_component_name(comp);
}

static const char* getLocation(icalcomponent *comp) {
    return icalcomponent_get_location(comp);
}

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy icalcomponent
    icalcomponent *comp = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Use the input data as strings
    std::string location(reinterpret_cast<const char*>(Data), Size);
    std::string x_name(reinterpret_cast<const char*>(Data), Size);

    // Set location
    setLocation(comp, location.c_str());

    // Get UID
    const char* uid = getUID(comp);
    if (uid) {
        std::cout << "UID: " << uid << std::endl;
    }

    // Set and get x_name
    setXName(comp, x_name.c_str());
    const char* retrieved_x_name = getXName(comp);
    if (retrieved_x_name) {
        std::cout << "X Name: " << retrieved_x_name << std::endl;
    }

    // Get component name
    const char* component_name = getComponentName(comp);
    if (component_name) {
        std::cout << "Component Name: " << component_name << std::endl;
    }

    // Get location
    const char* retrieved_location = getLocation(comp);
    if (retrieved_location) {
        std::cout << "Location: " << retrieved_location << std::endl;
    }

    // Clean up
    icalcomponent_free(comp);

    return 0;
}