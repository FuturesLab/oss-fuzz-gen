#include <sys/stat.h>
#include <string.h>
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
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    // Create a new VEVENT component
    icalcomponent *vevent = icalcomponent_new_vevent();
    if (!vevent) return 0;

    // Clone the VEVENT component
    icalcomponent *cloned_vevent = icalcomponent_clone(vevent);
    if (!cloned_vevent) {
        icalcomponent_free(vevent);
        return 0;
    }

    // Count properties in the VEVENT component
    int property_kind = ICAL_ANY_PROPERTY;
    if (Size >= 5) {
        property_kind = static_cast<int>(Data[4]) % ICAL_NO_PROPERTY;
    }
    int count = icalcomponent_count_properties(vevent, static_cast<icalproperty_kind>(property_kind));

    // Get summary of the VEVENT component
    const char *summary = icalcomponent_get_summary(vevent);

    // Create a new PARTICIPANT component
    icalcomponent *participant = icalcomponent_new_participant();
    if (!participant) {
        icalcomponent_free(vevent);
        icalcomponent_free(cloned_vevent);
        return 0;
    }

    // Get current component from PARTICIPANT
    icalcomponent *current_component = icalcomponent_get_current_component(participant);

    // Clean up
    icalcomponent_free(vevent);
    icalcomponent_free(cloned_vevent);
    icalcomponent_free(participant);

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

    LLVMFuzzerTestOneInput_36(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
