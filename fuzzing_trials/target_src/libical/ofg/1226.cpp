#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/icalmemory.h>
    #include <libical/icalparser.h> // Include for parsing iCalendar components
}

extern "C" int LLVMFuzzerTestOneInput_1226(const uint8_t *data, size_t size) {
    // Ensure that the size is non-zero to avoid passing 0 to icalmemory_new_buffer
    if (size == 0) {
        return 0;
    }

    // Allocate a new buffer with an additional byte for null-termination
    char *buffer = (char *)icalmemory_new_buffer(size + 1);

    // Copy the input data into the buffer
    if (buffer != NULL) {
        memcpy(buffer, data, size);
        buffer[size] = '\0'; // Null-terminate the buffer

        // Utilize the buffer by attempting to parse it as an iCalendar component
        icalparser *parser = icalparser_new();
        if (parser != NULL) {
            icalcomponent *component = icalparser_parse_string(buffer);
            if (component != NULL) {
                // If parsing is successful, free the component
                icalcomponent_free(component);
            }
            // Free the parser
            icalparser_free(parser);
        }

        // Clean up: free the allocated buffer
        free(buffer);
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

    LLVMFuzzerTestOneInput_1226(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
