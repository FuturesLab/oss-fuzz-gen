#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_909(const uint8_t *data, size_t size) {
    // Ensure that the data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to hold the input data as a string
    char *input_data = (char *)malloc(size + 1);
    if (input_data == NULL) {
        return 0;
    }

    // Copy the input data to the temporary buffer and null-terminate it
    memcpy(input_data, data, size);
    input_data[size] = '\0';

    // Convert the input data to an icalcomponent
    icalcomponent *component = icalparser_parse_string(input_data);

    // Free the temporary buffer
    free(input_data);

    // If the component was successfully created, convert it to an iCal string
    if (component != NULL) {
        char *ical_string = icalcomponent_as_ical_string_r(component);

        // Free the ical string if it was created
        if (ical_string != NULL) {
            free(ical_string);
        }

        // Free the icalcomponent
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_909(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
