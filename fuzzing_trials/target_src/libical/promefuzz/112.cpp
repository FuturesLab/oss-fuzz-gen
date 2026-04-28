// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalvalue_get_parent at icalvalue.c:1538:15 in icalproperty.h
// icalproperty_get_value at icalproperty.c:812:12 in icalproperty.h
// icalvalue_set_parent at icalvalue.c:1531:6 in icalproperty.h
// icalproperty_set_value at icalproperty.c:741:6 in icalproperty.h
// icalproperty_clone at icalproperty.c:92:15 in icalproperty.h
// icalproperty_free at icalproperty.c:176:6 in icalproperty.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
extern "C" {
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <icalproperty.h>
}

#include <cstdint>
#include <cstdlib>

static icalproperty_kind GetRandomPropertyKind(size_t index) {
    static const icalproperty_kind kinds[] = {
        ICAL_ANY_PROPERTY, ICAL_ACCEPTRESPONSE_PROPERTY, ICAL_ACKNOWLEDGED_PROPERTY,
        ICAL_ACTION_PROPERTY, ICAL_ALLOWCONFLICT_PROPERTY, ICAL_ATTACH_PROPERTY,
        ICAL_ATTENDEE_PROPERTY, ICAL_BUSYTYPE_PROPERTY, ICAL_CALENDARADDRESS_PROPERTY,
        ICAL_CALID_PROPERTY, ICAL_CALMASTER_PROPERTY, ICAL_CALSCALE_PROPERTY
        // Add more kinds as needed
    };
    return kinds[index % (sizeof(kinds) / sizeof(kinds[0]))];
}

extern "C" int LLVMFuzzerTestOneInput_112(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a new icalproperty and icalvalue
    icalproperty *property = icalproperty_new(GetRandomPropertyKind(Data[0]));
    if (!property) return 0;

    icalvalue *value = icalvalue_new_from_string(ICAL_STRING_VALUE, "Sample");
    if (!value) {
        icalproperty_free(property);
        return 0;
    }

    // Set the value for the property
    icalproperty_set_value(property, value);

    // Clone the property
    icalproperty *cloned_property = icalproperty_clone(property);
    if (cloned_property) {
        // Get the value from the cloned property
        icalvalue *cloned_value = icalproperty_get_value(cloned_property);
        if (cloned_value) {
            // Set parent for the cloned value
            icalvalue_set_parent(cloned_value, cloned_property);
        }

        // Free the cloned property
        icalproperty_free(cloned_property);
    }

    // Get the parent of the original value
    icalproperty *parent_property = icalvalue_get_parent(value);
    if (parent_property) {
        // Perform operations if needed
    }

    // Free the original property
    icalproperty_free(property);

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

        LLVMFuzzerTestOneInput_112(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    