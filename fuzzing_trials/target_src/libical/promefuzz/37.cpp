// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalcomponent_set_comment at icalcomponent.c:1769:6 in icalcomponent.h
// icalcomponent_set_location at icalcomponent.c:1920:6 in icalcomponent.h
// icalcomponent_set_x_name at icalcomponent.c:324:6 in icalcomponent.h
// icalcomponent_set_summary at icalcomponent.c:1734:6 in icalcomponent.h
// icalcomponent_get_summary at icalcomponent.c:1746:13 in icalcomponent.h
// icalcomponent_set_description at icalcomponent.c:1885:6 in icalcomponent.h
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
#include <cstring>
#include <iostream>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalcomponent.h"

// Helper function to create a new icalcomponent
static icalcomponent* create_component() {
    return icalcomponent_new(ICAL_VEVENT_COMPONENT);
}

// Helper function to safely extract a string from fuzz data
static const char* extract_string(const uint8_t* Data, size_t Size, size_t& offset) {
    if (offset >= Size) return nullptr;
    size_t len = strnlen(reinterpret_cast<const char*>(Data + offset), Size - offset);
    if (offset + len >= Size) return nullptr; // Ensure null terminator is within bounds
    const char* str = reinterpret_cast<const char*>(Data + offset);
    offset += len + 1; // Move past the string and null terminator
    return str;
}

extern "C" int LLVMFuzzerTestOneInput_37(const uint8_t* Data, size_t Size) {
    if (Size == 0) return 0;

    // Create a new icalcomponent
    icalcomponent* comp = create_component();
    if (!comp) return 0;

    size_t offset = 0;

    // Extract strings from the fuzz input
    const char* comment = extract_string(Data, Size, offset);
    const char* description = extract_string(Data, Size, offset);
    const char* location = extract_string(Data, Size, offset);
    const char* summary = extract_string(Data, Size, offset);
    const char* x_name = extract_string(Data, Size, offset);

    // Fuzz icalcomponent_set_comment
    if (comment) {
        icalcomponent_set_comment(comp, comment);
    }

    // Fuzz icalcomponent_set_description
    if (description) {
        icalcomponent_set_description(comp, description);
    }

    // Fuzz icalcomponent_set_location
    if (location) {
        icalcomponent_set_location(comp, location);
    }

    // Fuzz icalcomponent_set_summary
    if (summary) {
        icalcomponent_set_summary(comp, summary);
    }

    // Fuzz icalcomponent_get_summary
    const char* retrieved_summary = icalcomponent_get_summary(comp);
    if (retrieved_summary) {
        std::cout << "Retrieved Summary: " << retrieved_summary << std::endl;
    }

    // Fuzz icalcomponent_set_x_name
    if (x_name) {
        icalcomponent_set_x_name(comp, x_name);
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

        LLVMFuzzerTestOneInput_37(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    