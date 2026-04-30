#include <libical/ical.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include this for memcpy

extern "C" {
    // Wrap the C library functions and headers in extern "C"
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_118(const uint8_t *data, size_t size) {
    // Initialize an icalcomponent from the input data
    // For fuzzing purposes, let's assume the input data is a string representation of an iCalendar component
    char *ical_str = (char *)malloc(size + 1);
    if (ical_str == NULL) {
        return 0;
    }
    memcpy(ical_str, data, size);
    ical_str[size] = '\0';

    // Parse the string to create an icalcomponent
    icalcomponent *component = icalparser_parse_string(ical_str);
    if (component == NULL) {
        free(ical_str);
        return 0;
    }

    // Clone the icalcomponent
    icalcomponent *cloned_component = icalcomponent_clone(component);

    // Clean up
    icalcomponent_free(component);
    if (cloned_component != NULL) {
        icalcomponent_free(cloned_component);
    }
    free(ical_str);

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

    LLVMFuzzerTestOneInput_118(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
