// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_get_component_name_r at icalcomponent.c:353:7 in icalcomponent.h
// icalcomponent_new_x at icalcomponent.c:161:16 in icalcomponent.h
// icalcomponent_set_x_name at icalcomponent.c:324:6 in icalcomponent.h
// icalcomponent_get_component_name at icalcomponent.c:344:13 in icalcomponent.h
// icalcomponent_strip_errors at icalcomponent.c:1145:6 in icalcomponent.h
// icalcomponent_set_sequence at icalcomponent.c:1955:6 in icalcomponent.h
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
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include <icalcomponent.h>

extern "C" int LLVMFuzzerTestOneInput_105(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Create a new X component with a name derived from input data
    char *x_name = static_cast<char *>(malloc(Size + 1));
    if (!x_name) {
        return 0;
    }
    memcpy(x_name, Data, Size);
    x_name[Size] = '\0';

    icalcomponent *component = icalcomponent_new_x(x_name);
    free(x_name);

    if (!component) {
        return 0;
    }

    // Set X name with another portion of input data
    if (Size > 1) {
        char *new_x_name = static_cast<char *>(malloc(Size));
        if (new_x_name) {
            memcpy(new_x_name, Data + 1, Size - 1);
            new_x_name[Size - 1] = '\0';
            icalcomponent_set_x_name(component, new_x_name);
            free(new_x_name);
        }
    }

    // Set sequence number using the first byte of input data
    icalcomponent_set_sequence(component, Data[0]);

    // Strip errors, if any
    icalcomponent_strip_errors(component);

    // Retrieve component name
    const char *component_name = icalcomponent_get_component_name(component);
    if (component_name) {
        std::cout << "Component Name: " << component_name << std::endl;
    }

    // Retrieve component name with dynamic allocation
    char *component_name_r = icalcomponent_get_component_name_r(component);
    if (component_name_r) {
        std::cout << "Component Name R: " << component_name_r << std::endl;
        free(component_name_r);
    }

    // Cleanup
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

        LLVMFuzzerTestOneInput_105(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    