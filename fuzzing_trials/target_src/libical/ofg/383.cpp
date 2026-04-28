#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>  // Include string.h for memcpy

extern "C" {
#include <libical/ical.h>  // Wrap libical includes in extern "C"
}

extern "C" int LLVMFuzzerTestOneInput_383(const uint8_t *data, size_t size) {
    // Convert the input data to a null-terminated string
    char *input = (char *)malloc(size + 1);
    if (!input) {
        return 0;  // Exit if memory allocation fails
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Use the input data with a function that can parse it
    icalcomponent *component = icalparser_parse_string(input);

    // Clean up
    if (component) {
        icalcomponent_free(component);
    }
    free(input);

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

    LLVMFuzzerTestOneInput_383(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
