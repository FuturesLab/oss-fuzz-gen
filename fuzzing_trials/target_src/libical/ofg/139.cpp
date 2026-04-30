#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // For malloc and free
#include <string.h>  // For memcpy

extern "C" {
    // Ensure that all C headers and functions are wrapped in extern "C"
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_139(const uint8_t *data, size_t size) {
    // Ensure that the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a string from the input data
    char *ical_string = (char *)malloc(size + 1);
    if (ical_string == NULL) {
        return 0;
    }
    memcpy(ical_string, data, size);
    ical_string[size] = '\0';

    // Parse the string into an icalcomponent
    icalcomponent *component = icalparser_parse_string(ical_string);
    free(ical_string);

    if (component != NULL) {
        // Call the function-under-test
        icalcomponent *first_real_component = icalcomponent_get_first_real_component(component);

        // Clean up
        icalcomponent_free(component);
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_139(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
