#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include this header for strlen and strcpy

extern "C" {
#include <libical/icalparser.h>
#include <libical/icalcomponent.h>

// Define a mock line generator function
char* mock_line_gen_func_558(char *s, size_t size, void *data) {
    // For fuzzing, we just return a static line. In a real test, this could be dynamic.
    const char *line = "BEGIN:VCALENDAR\nVERSION:2.0\nEND:VCALENDAR";
    if (size < strlen(line) + 1) {
        return NULL;
    }
    strcpy(s, line);
    return s;
}

int LLVMFuzzerTestOneInput_558(const uint8_t *data, size_t size) {
    // Ensure the input size is non-zero
    if (size == 0) {
        return 0;
    }

    // Initialize the parser
    icalparser *parser = icalparser_new();
    if (parser == NULL) {
        return 0;
    }

    // Call the function-under-test
    icalcomponent *component = icalparser_parse(parser, mock_line_gen_func_558);
    
    // Clean up
    if (component != NULL) {
        icalcomponent_free(component);
    }
    icalparser_free(parser);

    return 0;
}

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

    LLVMFuzzerTestOneInput_558(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
