// This fuzz driver is generated for library libical, aiming to fuzz the following functions:
// icalparser_get_ctrl at icalparser.c:1337:22 in icalparser.h
// icalparser_set_ctrl at icalparser.c:1342:6 in icalparser.h
// icalparser_get_state at icalparser.c:1203:18 in icalparser.h
// icalparser_free at icalparser.c:103:6 in icalparser.h
// icalparser_new at icalparser.c:80:13 in icalparser.h
// icalparser_add_line at icalparser.c:641:16 in icalparser.h
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
#include <cstdio>
#include <cstring>
#include "ical.h"
#include "ical.h"
#include "ical.h"
#include "icalparser.h"

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Initialize the parser
    icalparser *parser = icalparser_new();
    if (!parser) return 0;

    // Set control characters handling
    icalparser_ctrl ctrl = static_cast<icalparser_ctrl>(Data[0] % 3);
    icalparser_set_ctrl(ctrl);

    // Check the current control setting
    icalparser_get_ctrl();

    // Feed data to the parser line by line
    char *line = static_cast<char *>(malloc(Size + 1));
    if (!line) {
        icalparser_free(parser);
        return 0;
    }
    memcpy(line, Data, Size);
    line[Size] = '\0';

    icalcomponent *component = icalparser_add_line(parser, line);

    // Free the component if it was created
    if (component) {
        icalcomponent_free(component);
    }

    // Check the parser state
    icalparser_get_state(parser);

    // Clean up
    free(line);
    icalparser_free(parser);

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

        LLVMFuzzerTestOneInput_28(data + 1, (size_t)(size - 1));

        free(data);
        fclose(f);
        return 0;
    }
    #endif
    