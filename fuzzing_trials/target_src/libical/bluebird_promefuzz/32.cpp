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
#include <vector>
#include <cstring>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalcomponent.h"

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(icalcomponent_kind)) {
        return 0;
    }

    // Prepare a dummy icalcomponent
    icalcomponent *parent = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    icalcomponent *child = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Add the child component to the parent
    icalcomponent_add_component(parent, child);

    // Initialize an iterator for the parent component
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES);
    icalcompiter iter = icalcomponent_begin_component(parent, kind);

    // Explore the iterator
    icalcomponent *current = nullptr;
    while ((current = icalcompiter_deref(&iter)) != nullptr) {
        // Get the inner component
        icalcomponent *inner = icalcomponent_get_inner(current);

        // Move to the next component
        icalcompiter_next(&iter);
    }

    // Try to get the previous component
    icalcomponent *prev = icalcompiter_prior(&iter);

    // Clean up
    icalcomponent_free(parent);

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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_32(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
