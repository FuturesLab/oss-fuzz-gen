#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_472(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to be useful
    if (size < 1) {
        return 0;
    }

    // Create a string from the input data
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0'; // Null-terminate the string

    // Parse the input data as an iCalendar component
    icalcomponent *component = icalparser_parse_string(input);

    // Check if the component is not NULL
    if (component != NULL) {
        // Perform any additional operations on the component if needed

        // Free the component to prevent memory leaks
        icalcomponent_free(component);
    }

    // Free the input string
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

    LLVMFuzzerTestOneInput_472(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
