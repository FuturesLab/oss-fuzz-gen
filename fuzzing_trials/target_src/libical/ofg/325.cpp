#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <libical/ical.h>

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
}

extern "C" int LLVMFuzzerTestOneInput_325(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < 1) {
        return 0;
    }

    // Create a temporary string from the fuzzing data
    char *ical_data = (char *)malloc(size + 1);
    if (ical_data == NULL) {
        return 0;
    }
    memcpy(ical_data, data, size);
    ical_data[size] = '\0'; // Null-terminate the string

    // Parse the string into an icalcomponent
    icalcomponent *component = icalparser_parse_string(ical_data);

    // Ensure the component is valid
    if (component != NULL) {
        // Call the function-under-test
        int sequence = icalcomponent_get_sequence(component);

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

    LLVMFuzzerTestOneInput_325(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
