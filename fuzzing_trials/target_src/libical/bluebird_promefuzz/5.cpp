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
#include "libical/ical.h"

static icalcomponent* create_dummy_icalcomponent(const uint8_t *Data, size_t Size) {
    // Attempt to parse the input data as an iCalendar string
    std::string ical_data(reinterpret_cast<const char*>(Data), Size);
    icalcomponent *component = icalparser_parse_string(ical_data.c_str());
    if (!component) {
        // If parsing fails, create a simple VEVENT component
        component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    }
    return component;
}

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    // Create a dummy icalcomponent from the input data
    icalcomponent *component = create_dummy_icalcomponent(Data, Size);
    if (!component) {
        return 0;
    }

    // Test icalcomponent_as_ical_string
    char *ical_string = icalcomponent_as_ical_string(component);
    if (ical_string) {
        std::cout << "iCal String: " << ical_string << std::endl;
    }

    // Test icalcomponent_get_uid
    const char *uid = icalcomponent_get_uid(component);
    if (uid) {
        std::cout << "UID: " << uid << std::endl;
    }

    // Test icalcomponent_get_comment
    const char *comment = icalcomponent_get_comment(component);
    if (comment) {
        std::cout << "Comment: " << comment << std::endl;
    }

    // Test icalcomponent_get_description
    const char *description = icalcomponent_get_description(component);
    if (description) {
        std::cout << "Description: " << description << std::endl;
    }

    // Test icalcomponent_get_component_name
    const char *component_name = icalcomponent_get_component_name(component);
    if (component_name) {
        std::cout << "Component Name: " << component_name << std::endl;
    }

    // Test icalcomponent_get_location
    const char *location = icalcomponent_get_location(component);
    if (location) {
        std::cout << "Location: " << location << std::endl;
    }

    // Clean up the component

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from icalcomponent_get_location to icalproperty_recurrence_is_excluded
    struct icaltimetype ret_icalcomponent_get_dtstart_wjavx = icalcomponent_get_dtstart(component);
    struct icaltimetype ret_icalcomponent_get_due_euiug = icalcomponent_get_due(component);

    bool ret_icalproperty_recurrence_is_excluded_venir = icalproperty_recurrence_is_excluded(component, &ret_icalcomponent_get_dtstart_wjavx, &ret_icalcomponent_get_due_euiug);
    if (ret_icalproperty_recurrence_is_excluded_venir == 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    icalcomponent_free(component);
    
    return 0;
}