#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_136(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a valid string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *icalString = (char *)malloc(size + 1);
    if (icalString == NULL) {
        return 0;
    }
    memcpy(icalString, data, size);
    icalString[size] = '\0';

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(icalString);
    if (component != NULL) {
        // Define a valid icalcomponent_kind for testing
        icalcomponent_kind kind = ICAL_VEVENT_COMPONENT;

        // Call the function-under-test
        int count = icalcomponent_count_components(component, kind);

        // Clean up
        icalcomponent_free(component);
    }

    free(icalString);
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

    LLVMFuzzerTestOneInput_136(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
