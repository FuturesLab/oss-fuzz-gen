#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for a null-terminated string
    char *ical_data = (char *)malloc(size + 1);
    if (ical_data == NULL) {
        return 0;
    }

    // Copy the input data into the string and null-terminate it
    memcpy(ical_data, data, size);
    ical_data[size] = '\0';

    // Create an icalcomponent from the input data
    icalcomponent *component = icalparser_parse_string(ical_data);

    if (component != NULL) {
        // Call the function-under-test
        char *ical_string = icalcomponent_as_ical_string(component);

        // Free the returned string if it was allocated
        if (ical_string != NULL) {
            free(ical_string);
        }

        // Free the icalcomponent
        icalcomponent_free(component);
    }

    // Free the allocated string
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_33(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
