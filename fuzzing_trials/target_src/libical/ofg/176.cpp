#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <libical/ical.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_176(const uint8_t *data, size_t size) {
    // Initialize the iCalendar component
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Create a temporary string buffer to hold the input data
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        return 0;
    }

    // Copy the input data into the string buffer and null-terminate it
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Parse the input data into the iCalendar component
    icalcomponent *parsedComponent = icalparser_parse_string(inputData);
    if (parsedComponent != NULL) {
        // Call the function-under-test
        struct icaltimetype dtend = icalcomponent_get_dtend(parsedComponent);

        // Clean up the parsed component
        icalcomponent_free(parsedComponent);
    }

    // Clean up the input data buffer
    free(inputData);

    // Clean up the initial component
    icalcomponent_free(component);

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

    LLVMFuzzerTestOneInput_176(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
