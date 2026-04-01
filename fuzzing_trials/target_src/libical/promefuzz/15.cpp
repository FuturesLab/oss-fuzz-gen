// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_free at icalcomponent.c:172:6 in icalcomponent.h
// icalcomponent_new_vagenda at icalcomponent.c:2070:16 in icalcomponent.h
// icalcomponent_add_component at icalcomponent.c:509:6 in icalcomponent.h
// icalcomponent_add_property at icalcomponent.c:385:6 in icalcomponent.h
// icalcomponent_set_dtstamp at icalcomponent.c:1710:6 in icalcomponent.h
// icalcomponent_merge_component at icalcomponent.c:2139:6 in icalcomponent.h
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
#include "ical.h"
#include <cstdint>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    std::ofstream dummyFile("./dummy_file", std::ios::binary);
    if (dummyFile.is_open()) {
        dummyFile.write(reinterpret_cast<const char*>(Data), Size);
        dummyFile.close();
    }
}

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Write the input data to a dummy file
    write_dummy_file(Data, Size);

    // Create two VCALENDAR components to test merging
    icalcomponent *vcalendar1 = icalcomponent_vanew(ICAL_VCALENDAR_COMPONENT, nullptr);
    icalcomponent *vcalendar2 = icalcomponent_vanew(ICAL_VCALENDAR_COMPONENT, nullptr);

    // Create a VAGENDA component
    icalcomponent *vagenda = icalcomponent_new_vagenda();
    if (vagenda) {
        icalcomponent_add_component(vcalendar1, vagenda);
    }

    // Add a property to vcalendar1
    icalproperty *property = icalproperty_new(ICAL_SUMMARY_PROPERTY);
    if (property) {
        icalcomponent_add_property(vcalendar1, property);
    }

    // Set a DTSTAMP on vcalendar1
    struct icaltimetype dtstamp = icaltime_from_timet_with_zone(time(nullptr), 0, nullptr);
    icalcomponent_set_dtstamp(vcalendar1, dtstamp);

    // Merge vcalendar2 into vcalendar1
    icalcomponent_merge_component(vcalendar1, vcalendar2);

    // Free the components
    icalcomponent_free(vcalendar1);
    // vcalendar2 should not be freed as it is merged into vcalendar1
    // vagenda and property are freed with vcalendar1

    return 0;
}