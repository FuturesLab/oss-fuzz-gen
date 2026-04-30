#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_229(const uint8_t *data, size_t size) {
    // Ensure that the function is called to create a new VPOLL component
    icalcomponent *vpoll_component = icalcomponent_new_vpoll();

    // Check if data is not null and size is greater than zero
    if (data != NULL && size > 0) {
        // Create a temporary buffer to hold the input data
        char *buffer = new char[size + 1];
        memcpy(buffer, data, size);
        buffer[size] = '\0'; // Null-terminate the buffer

        // Try to parse the data as an icalcomponent
        icalcomponent *parsed_component = icalparser_parse_string(buffer);

        // Clean up the parsed component to avoid memory leaks
        if (parsed_component != NULL) {
            icalcomponent_free(parsed_component);
        }

        // Clean up the buffer
        delete[] buffer;
    }

    // Clean up the created component to avoid memory leaks
    if (vpoll_component != NULL) {
        icalcomponent_free(vpoll_component);
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

    LLVMFuzzerTestOneInput_229(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
