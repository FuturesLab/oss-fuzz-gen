#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "libical/icalparser.h"
}

// A simple line generator function for testing
char* line_generator_126(char *buffer, unsigned long size, void* data) {
    static const char* lines[] = {
        "BEGIN:VCALENDAR",
        "VERSION:2.0",
        "BEGIN:VEVENT",
        "SUMMARY:Test Event",
        "END:VEVENT",
        "END:VCALENDAR"
    };
    static size_t index = 0;
    if (index < sizeof(lines) / sizeof(lines[0])) {
        strncpy(buffer, lines[index++], size);
        return buffer;
    }
    return NULL;
}

extern "C" int LLVMFuzzerTestOneInput_126(const uint8_t *data, size_t size) {
    // Initialize a icalparser object
    icalparser* parser = icalparser_new();

    if (parser == NULL) {
        return 0; // Return if parser creation fails
    }

    // Call the function-under-test
    char buffer[1024];
    char* line = NULL;
    while ((line = icalparser_get_line(parser, line_generator_126)) != NULL) {
        // Process the line if needed
        free(line); // Free the line if it was allocated
    }

    // Free the parser
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

    LLVMFuzzerTestOneInput_126(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
