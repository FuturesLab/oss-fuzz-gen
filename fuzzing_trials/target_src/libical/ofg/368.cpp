#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy

extern "C" {
    #include <libical/icalparser.h>
}

// Define a line generator function that matches the expected signature
extern "C" char *line_generator_368(char *s, unsigned long size, void *d) {
    static const uint8_t *data = nullptr;
    static size_t data_size = 0;
    static size_t offset = 0;

    if (d != NULL) {
        data = (const uint8_t *)d;
        data_size = size;
        offset = 0;
    }

    if (offset >= data_size) {
        return NULL;
    }

    size_t len = 0;
    while (offset < data_size && len < size - 1) {
        s[len++] = data[offset++];
        if (s[len - 1] == '\n') {  // Break on newline to simulate line-by-line reading
            break;
        }
    }
    s[len] = '\0';

    return s;
}

extern "C" int LLVMFuzzerTestOneInput_368(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    icalparser *parser = icalparser_new();

    if (parser == NULL) {
        return 0;
    }

    // Initialize the line generator with the input data
    line_generator_368(NULL, 0, (void *)data);

    // Use the line generator function with the parser
    icalcomponent *component = icalparser_parse(parser, line_generator_368);

    // Check if a component was returned and perform some operation on it
    if (component != NULL) {
        // Process the component to ensure code coverage
        icalcomponent_free(component);
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

    LLVMFuzzerTestOneInput_368(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
