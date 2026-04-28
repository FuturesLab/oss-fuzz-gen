#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_321(const uint8_t *data, size_t size) {
    // Ensure the size is large enough for a minimal iCalendar component
    if (size < 5) {
        return 0;
    }

    // Create a buffer to hold the input data and ensure it's null-terminated
    char *ical_data = (char *)malloc(size + 1);
    if (ical_data == NULL) {
        return 0;
    }
    memcpy(ical_data, data, size);
    ical_data[size] = '\0';

    // Parse the data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(ical_data);
    if (component != NULL) {
        // Call the function-under-test
        const char *comment = icalcomponent_get_comment(component);

        // Normally, you might do something with `comment` here,
        // but for fuzzing, we are just interested in calling the function.

        // Clean up
        icalcomponent_free(component);
    }

    free(ical_data);
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

    LLVMFuzzerTestOneInput_321(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
