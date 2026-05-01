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
#include <cstdint>
#include <cstdlib>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalcomponent.h"
#include <iostream>

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    // Initialize components using the target API functions
    icalcomponent *vresource = nullptr;
    icalcomponent *xstandard = nullptr;
    icalcomponent *vvoter = nullptr;
    icalcomponent *xdaylight = nullptr;
    icalcomponent *xpatch = nullptr;

    try {
        vresource = icalcomponent_new_vresource();
        xstandard = icalcomponent_new_xstandard();
        vvoter = icalcomponent_new_vvoter();
        xdaylight = icalcomponent_new_xdaylight();
        xpatch = icalcomponent_new_xpatch();

        // Create an array of components to add to a parent
        icalcomponent *components[] = {vresource, xstandard, vvoter, xdaylight, xpatch};

        // Create a parent component
        icalcomponent *parent = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);

        // Add each component to the parent
        for (icalcomponent *child : components) {
            if (child != nullptr && parent != nullptr) {
                icalcomponent_add_component(parent, child);
            }
        }

        // Clean up by freeing the parent component, which should recursively free children
        if (parent != nullptr) {
            icalcomponent_free(parent);
        } else {
            // Free components individually if parent creation failed
            for (icalcomponent *child : components) {
                if (child != nullptr) {
                    icalcomponent_free(child);
                }
            }
        }
    } catch (...) {
        // Catch all exceptions to prevent fuzzer from crashing
        std::cerr << "Exception caught during fuzzing" << std::endl;
    }

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

    LLVMFuzzerTestOneInput_21(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
