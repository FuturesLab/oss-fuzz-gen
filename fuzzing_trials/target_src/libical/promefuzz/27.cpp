// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_get_status at icalcomponent.c:2002:26 in icalcomponent.h
// icalcomponent_set_status at icalcomponent.c:1990:6 in icalcomponent.h
// icalcomponent_new_vtimezone at icalcomponent.c:2055:16 in icalcomponent.h
// icalcomponent_isa at icalcomponent.c:304:20 in icalcomponent.h
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
#include <cassert>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a new VTIMEZONE component
    icalcomponent *vtimezone = icalcomponent_new_vtimezone();
    assert(vtimezone != nullptr);

    // Create a new VALARM component
    icalcomponent *valarm = icalcomponent_new_valarm();
    assert(valarm != nullptr);

    // Determine the kind of the components
    icalcomponent_kind kind_vtimezone = icalcomponent_isa(vtimezone);
    icalcomponent_kind kind_valarm = icalcomponent_isa(valarm);

    // Set a summary for the VTIMEZONE component
    std::string summary(reinterpret_cast<const char*>(Data), Size);
    icalcomponent_set_summary(vtimezone, summary.c_str());

    // Get and set status for the VALARM component
    icalproperty_status status = icalcomponent_get_status(valarm);
    icalcomponent_set_status(valarm, ICAL_STATUS_TENTATIVE);

    // Clean up components
    icalcomponent_free(vtimezone);
    icalcomponent_free(valarm);

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

        LLVMFuzzerTestOneInput_27(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    