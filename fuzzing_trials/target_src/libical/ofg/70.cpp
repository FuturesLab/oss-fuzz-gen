#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_70(const uint8_t *data, size_t size) {
    // Create a new VEVENT component
    icalcomponent *vevent = icalcomponent_new_vevent();

    // Check if the function returned a non-null pointer
    if (vevent != NULL) {
        // Create a string from the input data
        char *input_data = (char *)malloc(size + 1);
        if (input_data != NULL) {
            memcpy(input_data, data, size);
            input_data[size] = '\0'; // Null-terminate the string

            // Parse the input data as an iCalendar property
            icalproperty *prop = icalproperty_new_from_string(input_data);
            if (prop != NULL) {
                // Add the property to the VEVENT component
                icalcomponent_add_property(vevent, prop);
            }

            free(input_data);
        }

        // Clean up and free the allocated component
        icalcomponent_free(vevent);
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

    LLVMFuzzerTestOneInput_70(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
