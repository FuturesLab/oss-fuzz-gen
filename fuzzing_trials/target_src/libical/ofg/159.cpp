#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy
#include <libical/ical.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_159(const uint8_t *data, size_t size) {
    // Create a temporary buffer to hold the input data
    char *buffer = (char *)malloc(size + 1);
    if (buffer == NULL) {
        return 0;
    }
    memcpy(buffer, data, size);
    buffer[size] = '\0'; // Null-terminate the buffer

    // Initialize an icalcomponent from the buffer
    icalcomponent *component = icalparser_parse_string(buffer);

    // If the component is successfully created, call the function-under-test
    if (component != NULL) {
        icalcomponent_convert_errors(component);
        icalcomponent_free(component);
    }

    // Free the allocated buffer
    free(buffer);

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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_159(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
