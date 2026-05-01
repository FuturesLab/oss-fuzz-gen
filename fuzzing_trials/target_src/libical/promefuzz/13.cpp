// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_get_x_name at icalcomponent.c:337:13 in icalcomponent.h
// icalcomponent_get_comment at icalcomponent.c:1781:13 in icalcomponent.h
// icalcomponent_get_description at icalcomponent.c:1897:13 in icalcomponent.h
// icalcomponent_get_relcalid at icalcomponent.c:2591:13 in icalcomponent.h
// icalcomponent_get_uid at icalcomponent.c:1816:13 in icalcomponent.h
// icalcomponent_get_summary at icalcomponent.c:1746:13 in icalcomponent.h
#include <iostream>
#include <cstdint>
#include <cstddef>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(icalcomponent_kind)) {
        return 0;
    }

    // Create a dummy icalcomponent with the kind from the input data
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES);
    icalcomponent *comp = icalcomponent_new(kind);

    // Invoke each target function with the component
    const char *x_name = icalcomponent_get_x_name(comp);
    const char *relcalid = icalcomponent_get_relcalid(comp);
    const char *uid = icalcomponent_get_uid(comp);
    const char *description = icalcomponent_get_description(comp);
    const char *summary = icalcomponent_get_summary(comp);
    const char *comment = icalcomponent_get_comment(comp);

    // Check returned values (not strictly necessary for fuzzing, but good practice)
    if (x_name) {
        // Process x_name if needed
    }
    if (relcalid) {
        // Process relcalid if needed
    }
    if (uid) {
        // Process uid if needed
    }
    if (description) {
        // Process description if needed
    }
    if (summary) {
        // Process summary if needed
    }
    if (comment) {
        // Process comment if needed
    }

    // Clean up
    icalcomponent_free(comp);

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

        LLVMFuzzerTestOneInput_13(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    