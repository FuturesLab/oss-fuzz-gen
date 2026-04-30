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
#include <cstdio>
#include <cstring>
#include "libical/ical.h"
#include "libical/ical.h"
#include "libical/ical.h"
#include "/src/libical/src/libical/icalparser.h"

extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size) {
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_52(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
