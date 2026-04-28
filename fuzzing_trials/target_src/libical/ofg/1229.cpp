#include <cstdint>  // Include for uint8_t
#include <cstddef>  // Include for size_t
#include <cstring>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1229(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalparser *parser = icalparser_new();

    // Check if the parser was created successfully
    if (parser != NULL) {
        // Use the parser with the provided data
        // Convert the input data to a string, as icalparser_parse_string expects a string
        char *input = new char[size + 1];
        memcpy(input, data, size);
        input[size] = '\0';

        // Parse the input string
        icalcomponent *component = icalparser_parse_string(input);

        // Clean up the parser and input after usage
        icalparser_free(parser);
        delete[] input;

        // Free the component if it was created
        if (component != NULL) {
            icalcomponent_free(component);
        }
    }

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

    LLVMFuzzerTestOneInput_1229(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
