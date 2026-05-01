#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
    // Initialize the iCal library
    icalcomponent *component = nullptr;

    // Create a temporary buffer to hold the data
    char *buffer = (char *)malloc(size + 1);
    if (buffer == nullptr) {
        return 0;
    }

    // Copy the data into the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Parse the data into an icalcomponent
    component = icalparser_parse_string(buffer);

    // If parsing was successful, check if the component is valid
    if (component != nullptr) {
        bool is_valid = icalcomponent_is_valid(component);

        // Clean up the component
        icalcomponent_free(component);
    }

    // Free the buffer
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

    LLVMFuzzerTestOneInput_62(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
