// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_set_location at icalcomponent.c:1920:6 in icalcomponent.h
// icalcomponent_get_x_name at icalcomponent.c:337:13 in icalcomponent.h
// icalcomponent_get_description at icalcomponent.c:1897:13 in icalcomponent.h
// icalcomponent_set_description at icalcomponent.c:1885:6 in icalcomponent.h
// icalcomponent_new_from_string at icalcomponent.c:124:16 in icalcomponent.h
// icalcomponent_get_location at icalcomponent.c:1932:13 in icalcomponent.h
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

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Convert input data to a string
    std::string input(reinterpret_cast<const char*>(Data), Size);

    // Create icalcomponent from input string
    icalcomponent *comp = icalcomponent_new_from_string(input.c_str());

    if (comp != NULL) {
        // Fuzz icalcomponent_set_description
        icalcomponent_set_description(comp, "Sample Description");

        // Fuzz icalcomponent_get_description
        const char *description = icalcomponent_get_description(comp);
        if (description) {
            std::cout << "Description: " << description << std::endl;
        }

        // Fuzz icalcomponent_set_location
        icalcomponent_set_location(comp, "Sample Location");

        // Fuzz icalcomponent_get_location
        const char *location = icalcomponent_get_location(comp);
        if (location) {
            std::cout << "Location: " << location << std::endl;
        }

        // Fuzz icalcomponent_get_x_name
        const char *x_name = icalcomponent_get_x_name(comp);
        if (x_name) {
            std::cout << "X-Name: " << x_name << std::endl;
        }

        // Clean up
        icalcomponent_free(comp);
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

        LLVMFuzzerTestOneInput_30(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    