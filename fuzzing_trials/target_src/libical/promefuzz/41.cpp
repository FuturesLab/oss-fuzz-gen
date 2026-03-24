// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_get_timezone at icalcomponent.c:2430:15 in icalcomponent.h
// icalcomponent_new_from_string at icalcomponent.c:124:16 in icalcomponent.h
// icalcomponent_get_summary at icalcomponent.c:1746:13 in icalcomponent.h
// icalcomponent_new_vevent at icalcomponent.c:2030:16 in icalcomponent.h
// icalcomponent_merge_component at icalcomponent.c:2139:6 in icalcomponent.h
// icalcomponent_add_component at icalcomponent.c:509:6 in icalcomponent.h
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
#include "ical.h"
#include <string>

static icalcomponent* createDummyVCalendar() {
    icalcomponent* vcalendar = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    icalcomponent* vevent = icalcomponent_new_vevent();
    icalcomponent_add_component(vcalendar, vevent);
    return vcalendar;
}

static void writeToFile(const char* path, const uint8_t* data, size_t size) {
    std::ofstream file(path, std::ios::binary);
    file.write(reinterpret_cast<const char*>(data), size);
    file.close();
}

extern "C" int LLVMFuzzerTestOneInput_41(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Step 1: Test icalcomponent_new_from_string
    std::string icalString(reinterpret_cast<const char*>(Data), Size);
    icalcomponent* component = icalcomponent_new_from_string(icalString.c_str());
    
    if (component) {
        // Step 2: Test icalcomponent_get_timezone
        icaltimezone* timezone = icalcomponent_get_timezone(component, "TZID");
        
        // Step 3: Test icalcomponent_get_summary
        const char* summary = icalcomponent_get_summary(component);
        
        // Step 4: Test icalcomponent_merge_component
        icalcomponent* vcalendar = createDummyVCalendar();
        icalcomponent_merge_component(vcalendar, component);
        
        // Cleanup
        icalcomponent_free(vcalendar);
    }

    // Step 5: Test icalcomponent_add_component
    icalcomponent* parent = createDummyVCalendar();
    icalcomponent* child = icalcomponent_new_vevent();
    icalcomponent_add_component(parent, child);

    // Cleanup
    icalcomponent_free(parent);

    // Step 6: Write data to a dummy file and test icalcomponent_new_from_string again
    writeToFile("./dummy_file", Data, Size);
    icalcomponent* fileComponent = icalcomponent_new_from_string(icalString.c_str());
    if (fileComponent) {
        icalcomponent_free(fileComponent);
    }

    return 0;
}