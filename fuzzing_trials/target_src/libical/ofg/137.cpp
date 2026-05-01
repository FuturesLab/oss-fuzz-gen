#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h> // For malloc and free
#include <string.h> // For memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_137(const uint8_t *data, size_t size) {
    // Initialize a string from the input data
    char *input_data = (char *)malloc(size + 1);
    if (input_data == NULL) {
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0';

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(input_data);
    if (component == NULL) {
        free(input_data);
        return 0;
    }

    // Define a valid icalcomponent_kind
    icalcomponent_kind kind = ICAL_VEVENT_COMPONENT;

    // Call the function under test
    int count = icalcomponent_count_components(component, kind);

    // Clean up
    icalcomponent_free(component);
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_137(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
