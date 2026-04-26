#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_252(const uint8_t *data, size_t size) {
    // Ensure we have enough data to work with
    if (size == 0) {
        return 0;
    }

    // Initialize the timezone object
    const icaltimezone *zone = icaltimezone_get_utc_timezone();

    // Create a temporary buffer to hold the input data as a string
    char *input_data = (char *)malloc(size + 1);
    if (!input_data) {
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0'; // Null-terminate the string

    // Parse the input data as an iCalendar component
    icalcomponent *comp = icalparser_parse_string(input_data);

    // Check if parsing was successful
    if (comp != NULL) {
        // Use the component in some way to avoid compiler optimizations
        icalcomponent_kind kind = icalcomponent_isa(comp);
        if (kind != ICAL_NO_COMPONENT) {
            // Do something with the component if needed
        }

        // Free the component after use
        icalcomponent_free(comp);
    }

    // Free the allocated input data buffer
    free(input_data);

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

    LLVMFuzzerTestOneInput_252(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
