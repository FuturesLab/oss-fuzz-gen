#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include this header for memcpy

extern "C" {
    #include <libical/ical.h>
    #include <libical/icalmemory.h>
    #include <libical/icalparser.h>
}

extern "C" int LLVMFuzzerTestOneInput_1271(const uint8_t *data, size_t size) {
    // Convert the input data to a string
    char *input = (char *)icalmemory_new_buffer(size + 1);
    if (input == NULL) {
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Parse the input data as an iCalendar component
    icalcomponent *comp = icalparser_parse_string(input);

    // Perform additional operations if necessary
    if (comp != NULL) {
        // Clean up the component if it's not NULL
        icalcomponent_free(comp);
    }

    // Free the allocated memory for the input string
    icalmemory_free_buffer(input);

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

    LLVMFuzzerTestOneInput_1271(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
