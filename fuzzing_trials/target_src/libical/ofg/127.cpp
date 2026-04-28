#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h> // Correctly include the libical header
}

// A simple line generation function for testing
static char* line_gen_func_127(char *s, size_t size, void *data) {
    static const char* lines[] = {
        "BEGIN:VCALENDAR",
        "VERSION:2.0",
        "BEGIN:VEVENT",
        "SUMMARY:Sample Event",
        "END:VEVENT",
        "END:VCALENDAR"
    };
    static int index = 0;
    if (index < sizeof(lines) / sizeof(lines[0])) {
        strncpy(s, lines[index++], size - 1);
        s[size - 1] = '\0'; // Ensure null-termination
        return s;
    }
    return NULL;
}

extern "C" int LLVMFuzzerTestOneInput_127(const uint8_t *data, size_t size) {
    // Initialize the icalparser object
    icalparser *parser = icalparser_new();
    if (parser == NULL) {
        return 0; // If parser creation fails, exit
    }

    // Allocate a buffer for line generation
    char buffer[256];

    // Use a simple line generation function
    icalparser_line_gen_func gen_func = line_gen_func_127;

    // Feed the input data to the parser
    const char *input_data = reinterpret_cast<const char*>(data);
    size_t input_size = size < 256 ? size : 255; // Limit size to buffer capacity
    strncpy(buffer, input_data, input_size);
    buffer[input_size] = '\0'; // Ensure null-termination

    // Call the function-under-test with correct arguments
    char *line = buffer;
    while (line != NULL) {
        line = icalparser_get_line(parser, gen_func);
        // Process the line if needed
        if (line != NULL) {
            free(line);
        }
    }

    // Clean up
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

    LLVMFuzzerTestOneInput_127(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
