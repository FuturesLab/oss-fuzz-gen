// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_strip_errors at icalcomponent.c:1145:6 in icalcomponent.h
// icalcomponent_convert_errors at icalcomponent.c:1168:6 in icalcomponent.h
// icalcomponent_clone at icalcomponent.c:129:16 in icalcomponent.h
// icalcomponent_free at icalcomponent.c:172:6 in icalcomponent.h
// icalcomponent_count_errors at icalcomponent.c:1123:5 in icalcomponent.h
// icalcomponent_check_restrictions at icalcomponent.c:1117:6 in icalcomponent.h
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
#include <cstdint>
#include <cstring>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"

static icalcomponent* createComponentFromData(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(icalcomponent_kind)) {
        return nullptr;
    }
    
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(Data[0] % ICAL_NUM_COMPONENT_TYPES);
    icalcomponent *component = icalcomponent_new(kind);
    
    // Additional setup of the component can be done here based on Data
    
    return component;
}

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    icalcomponent *component = createComponentFromData(Data, Size);
    if (!component) {
        return 0;
    }

    // Test icalcomponent_strip_errors
    icalcomponent_strip_errors(component);

    // Test icalcomponent_convert_errors
    icalcomponent_convert_errors(component);

    // Test icalcomponent_count_errors
    int error_count = icalcomponent_count_errors(component);
    (void)error_count;  // Suppress unused variable warning

    // Test icalcomponent_clone
    icalcomponent *cloned_component = icalcomponent_clone(component);
    if (cloned_component) {
        icalcomponent_free(cloned_component);
    }

    // Test icalcomponent_check_restrictions
    bool restrictions_ok = icalcomponent_check_restrictions(component);
    (void)restrictions_ok;  // Suppress unused variable warning

    // Clean up
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

        LLVMFuzzerTestOneInput_35(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    