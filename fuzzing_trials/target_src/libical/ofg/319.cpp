#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_319(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Initialize an icalcomponent from the input data
    char *ical_string = static_cast<char *>(malloc(size + 1));
    if (ical_string == NULL) {
        return 0;
    }

    memcpy(ical_string, data, size);
    ical_string[size] = '\0';

    icalcomponent *component = icalparser_parse_string(ical_string);

    if (component != NULL) {
        // Call the function-under-test
        icalcomponent *current_component = icalcomponent_get_current_component(component);

        // Clean up
        icalcomponent_free(component);
    }

    free(ical_string);
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

    LLVMFuzzerTestOneInput_319(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
