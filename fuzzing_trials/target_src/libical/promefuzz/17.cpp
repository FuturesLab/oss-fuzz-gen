// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_set_recurrenceid at icalcomponent.c:1839:6 in icalcomponent.h
// icalcomponent_get_dtstamp at icalcomponent.c:1722:21 in icalcomponent.h
// icalcomponent_get_dtstart at icalcomponent.c:1553:21 in icalcomponent.h
// icalcomponent_set_dtstart at icalcomponent.c:1533:6 in icalcomponent.h
// icalcomponent_get_recurrenceid at icalcomponent.c:1859:21 in icalcomponent.h
// icalproperty_get_datetime_with_component at icalproperty.c:1050:21 in icalcomponent.h
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
#include <libical/icalcomponent.h>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <libical/icalproperty.h>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <libical/icaltime.h>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <libical/ical.h>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0; // Exit if there's no data to process
    }

    // Ensure the input data is null-terminated for safe string operations
    std::vector<char> nullTerminatedData(Data, Data + Size);
    nullTerminatedData.push_back('\0');

    // Create a dummy iCalendar file with the input data
    std::ofstream dummyFile("./dummy_file.ics", std::ios::binary);
    dummyFile.write(reinterpret_cast<const char*>(nullTerminatedData.data()), Size);
    dummyFile.close();

    // Load the iCalendar component from the dummy file
    icalcomponent *component = icalparser_parse_string(nullTerminatedData.data());
    if (!component) {
        return 0; // If parsing fails, exit early
    }

    // Test icalcomponent_get_dtstamp
    icaltimetype dtstamp = icalcomponent_get_dtstamp(component);
    if (!icaltime_is_null_time(dtstamp)) {
        std::cout << "DTSTAMP: " << icaltime_as_ical_string(dtstamp) << std::endl;
    }

    // Test icalcomponent_get_recurrenceid
    icaltimetype recurrenceid = icalcomponent_get_recurrenceid(component);
    if (!icaltime_is_null_time(recurrenceid)) {
        std::cout << "RECURRENCE-ID: " << icaltime_as_ical_string(recurrenceid) << std::endl;
    }

    // Test icalcomponent_set_dtstart
    icaltimetype dtstart = icaltime_from_string("20231010T100000Z");
    icalcomponent_set_dtstart(component, dtstart);

    // Test icalcomponent_get_dtstart
    icaltimetype retrieved_dtstart = icalcomponent_get_dtstart(component);
    if (!icaltime_is_null_time(retrieved_dtstart)) {
        std::cout << "DTSTART: " << icaltime_as_ical_string(retrieved_dtstart) << std::endl;
    }

    // Test icalcomponent_set_recurrenceid
    icaltimetype new_recurrenceid = icaltime_from_string("20231011T110000Z");
    icalcomponent_set_recurrenceid(component, new_recurrenceid);

    // Create a dummy property to test icalproperty_get_datetime_with_component
    icalproperty *property = icalproperty_new_dtstart(dtstart);
    if (property) {
        icaltimetype datetime = icalproperty_get_datetime_with_component(property, component);
        if (!icaltime_is_null_time(datetime)) {
            std::cout << "DATETIME: " << icaltime_as_ical_string(datetime) << std::endl;
        }
        icalproperty_free(property);
    }

    // Clean up the component
    icalcomponent_free(component);

    return 0;
}
    #ifdef INC_MAIN
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdint.h>
    int main(int argc, char *argv[])
    {
        FILE *f;
        uint8_t *data = NULL;
        long size;

        if(argc < 2)
            exit(0);

        f = fopen(argv[1], "rb");
        if(f == NULL)
            exit(0);

        fseek(f, 0, SEEK_END);

        size = ftell(f);
        rewind(f);

        if(size < 1 + 1)
            exit(0);

        data = (uint8_t *)malloc((size_t)size);
        if(data == NULL)
            exit(0);

        if(fread(data, (size_t)size, 1, f) != 1)
            exit(0);

        LLVMFuzzerTestOneInput_17(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    