#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // Include for malloc and free
#include <string.h>  // Include for memcpy

extern "C" {
    // Include necessary C headers from the libical project
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_169(const uint8_t *data, size_t size) {
    // Initialize the library if necessary
    icalcomponent *root_component = nullptr;
    icalcomponent *next_component = nullptr;
    icalcomponent_kind kind = ICAL_ANY_COMPONENT;

    // Create a new icalcomponent from the input data
    // Ensure that the data is null-terminated for parsing
    char *ical_data = (char *)malloc(size + 1);
    if (ical_data == nullptr) {
        return 0;
    }
    memcpy(ical_data, data, size);
    ical_data[size] = '\0';

    root_component = icalparser_parse_string(ical_data);
    free(ical_data);

    if (root_component != nullptr) {
        // Fuzz different component kinds
        next_component = icalcomponent_get_next_component(root_component, kind);

        // Clean up
        icalcomponent_free(root_component);
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

    LLVMFuzzerTestOneInput_169(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
