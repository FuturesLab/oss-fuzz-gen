#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include "libical/ical.h"
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent
    icalcomponent *comp = icalcomponent_new(ICAL_VTODO_COMPONENT);
    if (comp == NULL) {
        return 0; // Exit if the component could not be created
    }

    // Initialize the icaltimetype struct
    struct icaltimetype due_time;
    if (size >= sizeof(struct icaltimetype)) {
        // Copy data into due_time if enough data is provided
        memcpy(&due_time, data, sizeof(struct icaltimetype));
    } else {
        // Otherwise, initialize with default values
        due_time = icaltime_null_time();
    }

    // Ensure the due_time is valid before using it
    if (!icaltime_is_null_time(due_time)) {
        // Set a valid timezone to prevent crashes
        icaltimezone *zone = icaltimezone_get_builtin_timezone("UTC");
        if (zone != NULL) {
            due_time.zone = zone;
        }

        // Call the function-under-test
        icalcomponent_set_due(comp, due_time);
    }

    // Clean up
    icalcomponent_free(comp);

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

    LLVMFuzzerTestOneInput_55(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
