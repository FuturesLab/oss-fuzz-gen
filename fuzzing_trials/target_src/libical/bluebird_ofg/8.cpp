#include <sys/stat.h>
#include "libical/ical.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h> // For malloc and free
#include <string.h> // For memcpy

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
}

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Initialize variables
    icalcomponent *component = icalcomponent_new(ICAL_VTIMEZONE_COMPONENT);
    icaltimetype start_time = icaltime_from_timet_with_zone(0, false, NULL);
    icaltimetype end_time = icaltime_from_timet_with_zone(0, false, NULL);
    bool is_truncated = true;

    // Ensure the data size is sufficient to manipulate the component
    if (size > 0) {
        // Create a temporary buffer to hold the data
        char *temp_data = (char *)malloc(size + 1);
        if (temp_data == NULL) {
            icalcomponent_free(component);
            return 0;
        }

        // Copy the data into the temporary buffer and null-terminate it
        memcpy(temp_data, data, size);
        temp_data[size] = '\0';

        // Convert the data to a string and add it to the component as a property
        icalproperty *prop = icalproperty_new_comment(temp_data);
        icalcomponent_add_property(component, prop);

        // Free the temporary buffer
        free(temp_data);
    }

    // Call the function-under-test
    icaltimezone_truncate_vtimezone(component, start_time, end_time, is_truncated);

    // Clean up
    icalcomponent_free(component);

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

    LLVMFuzzerTestOneInput_8(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
