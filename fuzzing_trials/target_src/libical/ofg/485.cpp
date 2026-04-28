#include <cstdint>  // Include for uint8_t
#include <cstddef>  // Include for size_t
#include <cstring>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_485(const uint8_t *data, size_t size) {
    // Check if the input data is sufficient to create a valid string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *ical_data = new char[size + 1];
    memcpy(ical_data, data, size);
    ical_data[size] = '\0';

    // Parse the iCalendar data
    icalcomponent *component = icalparser_parse_string(ical_data);

    // Perform operations on the component if necessary
    if (component != NULL) {
        // Clean up the component to avoid memory leaks
        icalcomponent_free(component);
    }

    // Clean up the allocated string
    delete[] ical_data;

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

    LLVMFuzzerTestOneInput_485(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
