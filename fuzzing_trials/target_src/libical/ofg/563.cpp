#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_563(const uint8_t *data, size_t size) {
    // Ensure the data size is non-zero and manageable
    if (size == 0) return 0;

    // Allocate memory for the input string and ensure it's null-terminated
    char *inputString = (char *)malloc(size + 1);
    if (inputString == NULL) return 0;

    memcpy(inputString, data, size);
    inputString[size] = '\0';

    // Initialize the parser
    icalparser *parser = icalparser_new();
    if (parser == NULL) {
        free(inputString);
        return 0;
    }

    // Call the function-under-test
    icalcomponent *component = icalparser_add_line(parser, inputString);

    // Clean up
    if (component != NULL) {
        icalcomponent_free(component);
    }
    icalparser_free(parser);
    free(inputString);

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

    LLVMFuzzerTestOneInput_563(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
