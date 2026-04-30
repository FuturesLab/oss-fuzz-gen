#include <sys/stat.h>
#include "libical/ical.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to prevent buffer overflows
    if (size == 0 || data[size - 1] != '\0') {
        // Create a new buffer with an additional null terminator
        uint8_t *null_terminated_data = new uint8_t[size + 1];
        memcpy(null_terminated_data, data, size);
        null_terminated_data[size] = '\0';

        // Initialize the library
        icalcomponent *component = icalcomponent_new_from_string((const char *)null_terminated_data);
        delete[] null_terminated_data; // Clean up the temporary buffer

        if (component == NULL) {
            return 0; // If the component is NULL, return early
        }

        // Initialize an icalcompiter
        icalcompiter iter;
        iter = icalcomponent_begin_component(component, ICAL_ANY_COMPONENT);

        // Fuzz the function icalcompiter_next
        icalcomponent *next_component = icalcompiter_next(&iter);

        // Clean up
        icalcomponent_free(component);
    } else {
        // Initialize the library directly if data is already null-terminated
        icalcomponent *component = icalcomponent_new_from_string((const char *)data);
        if (component == NULL) {
            return 0; // If the component is NULL, return early
        }

        // Initialize an icalcompiter
        icalcompiter iter;
        iter = icalcomponent_begin_component(component, ICAL_ANY_COMPONENT);

        // Fuzz the function icalcompiter_next
        icalcomponent *next_component = icalcompiter_next(&iter);

        // Clean up
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_26(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
