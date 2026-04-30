#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h> // Correct include path for libical
}

extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a valid icalcomponent
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to hold the input data
    char *buffer = new char[size + 1];
    memcpy(buffer, data, size);
    buffer[size] = '\0'; // Null-terminate the buffer

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(buffer);

    // If parsing is successful, normalize the component
    if (component != nullptr) {
        icalcomponent_normalize(component);

        // Clean up
        icalcomponent_free(component);
    }

    delete[] buffer;
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

    LLVMFuzzerTestOneInput_49(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
