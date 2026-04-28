#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h> // Include this for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_369(const uint8_t *data, size_t size) {
    // Initialize the parser
    icalparser *parser = icalparser_new();

    // Ensure the parser is not NULL
    if (parser == NULL) {
        return 0;
    }

    // Convert the input data to a null-terminated string
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        icalparser_free(parser);
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Feed the input to the parser
    icalcomponent *component = icalparser_parse_string(input);

    // Free the input string
    free(input);

    // Check if the component is not NULL
    if (component != NULL) {
        // Do something with the component if needed
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

    LLVMFuzzerTestOneInput_369(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
