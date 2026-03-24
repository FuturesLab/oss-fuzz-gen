// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_new_vlocation at icalcomponent.c:2125:16 in icalcomponent.h
// icalcomponent_new_vevent at icalcomponent.c:2030:16 in icalcomponent.h
// icalcomponent_new_vfreebusy at icalcomponent.c:2050:16 in icalcomponent.h
// icalcomponent_new_vavailability at icalcomponent.c:2085:16 in icalcomponent.h
// icalcomponent_new_vcalendar at icalcomponent.c:2025:16 in icalcomponent.h
// icalcomponent_new_vresource at icalcomponent.c:2130:16 in icalcomponent.h
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
#include "ical.h"

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size) {
    // Prepare environment
    icalcomponent *comp_vavailability = nullptr;
    icalcomponent *comp_vlocation = nullptr;
    icalcomponent *comp_vfreebusy = nullptr;
    icalcomponent *comp_vevent = nullptr;
    icalcomponent *comp_vresource = nullptr;
    icalcomponent *comp_vcalendar = nullptr;

    try {
        // Invoke target functions
        comp_vavailability = icalcomponent_new_vavailability();
        comp_vlocation = icalcomponent_new_vlocation();
        comp_vfreebusy = icalcomponent_new_vfreebusy();
        comp_vevent = icalcomponent_new_vevent();
        comp_vresource = icalcomponent_new_vresource();
        comp_vcalendar = icalcomponent_new_vcalendar();

        // Simulate diverse usage
        if (Size > 0 && Data[0] % 2 == 0) {
            icalcomponent_add_component(comp_vcalendar, comp_vevent);
            icalcomponent_add_component(comp_vcalendar, comp_vavailability);
        } else {
            icalcomponent_add_component(comp_vcalendar, comp_vlocation);
            icalcomponent_add_component(comp_vcalendar, comp_vfreebusy);
        }

        // Write to a dummy file if needed
        std::ofstream dummyFile("./dummy_file");
        if (dummyFile.is_open()) {
            dummyFile << "BEGIN:VCALENDAR\n";
            dummyFile << "VERSION:2.0\n";
            dummyFile << "PRODID:-//Example Corp//NONSGML Event//EN\n";
            dummyFile << "END:VCALENDAR\n";
            dummyFile.close();
        }

    } catch (...) {
        // Handle any exceptions
    }

    // Cleanup
    if (comp_vavailability) icalcomponent_free(comp_vavailability);
    if (comp_vlocation) icalcomponent_free(comp_vlocation);
    if (comp_vfreebusy) icalcomponent_free(comp_vfreebusy);
    if (comp_vevent) icalcomponent_free(comp_vevent);
    if (comp_vresource) icalcomponent_free(comp_vresource);
    if (comp_vcalendar) icalcomponent_free(comp_vcalendar);

    return 0;
}