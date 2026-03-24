#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "libical/ical.h"
#include "libical/ical.h"

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) + sizeof(int)) {
        return 0;
    }

    // Create a dummy file if needed
    std::ofstream dummyFile("./dummy_file");
    if (!dummyFile.is_open()) {
        return 0;
    }
    dummyFile.write(reinterpret_cast<const char*>(Data), Size);
    dummyFile.close();

    // Extract data from input
    int year = *reinterpret_cast<const int*>(Data);
    Data += sizeof(int);
    Size -= sizeof(int);

    int componentType = *reinterpret_cast<const int*>(Data);
    Data += sizeof(int);
    Size -= sizeof(int);

    // Initialize timezone
    icaltimezone *timezone = icaltimezone_get_utc_timezone();

    // Initialize icaltimetype
    icaltimetype timeType;
    timeType.year = year;
    timeType.zone = timezone;

    // Initialize icalcomponent
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(componentType % ICAL_NUM_COMPONENT_TYPES);
    icalcomponent *component = icalcomponent_new(kind);

    if (!component) {
        return 0;
    }

    // Fuzz the target functions
    try {
        // icalcomponent_set_due
        if (kind == ICAL_VTODO_COMPONENT) {

            // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalcomponent_set_due with icalcomponent_set_dtend
            icalcomponent_set_dtend(component, timeType);
            // End mutation: Producer.REPLACE_FUNC_MUTATOR


        }

        // icalcomponent_set_dtstart
        icalcomponent_set_dtstart(component, timeType);

        // icalcomponent_set_dtend

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function icalcomponent_set_dtend with icalcomponent_set_recurrenceid
        icalcomponent_set_recurrenceid(component, timeType);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR



        // icalcomponent_set_recurrenceid
        icalcomponent_set_recurrenceid(component, timeType);

        // icalcomponent_set_dtstamp
        icalcomponent_set_dtstamp(component, timeType);

        // icalcomponent_new_valarm
        icalcomponent *valarm = icalcomponent_new_valarm();
        if (valarm) {
            icalcomponent_free(valarm);
        }
    } catch (...) {
        // Handle any exceptions
    }

    // Cleanup
    icalcomponent_free(component);

    return 0;
}