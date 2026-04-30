#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include string.h for memcpy

// Wrap the C headers and functions in extern "C"
extern "C" {
    #include <libical/icalcomponent.h>
    #include <libical/icalparser.h>
}

extern "C" int LLVMFuzzerTestOneInput_855(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for a null-terminated string
    char *ical_string = (char *)malloc(size + 1);
    if (ical_string == NULL) {
        return 0;
    }

    // Copy data to ical_string and null-terminate it
    memcpy(ical_string, data, size);
    ical_string[size] = '\0';

    // Parse the data into an icalcomponent
    icalcomponent *comp = icalparser_parse_string(ical_string);

    // Free the allocated string memory
    free(ical_string);

    // If parsing was successful, call the function-under-test
    if (comp != NULL) {
        icalcomponent_strip_errors(comp);

        // Clean up the icalcomponent
        icalcomponent_free(comp);
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_855(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
