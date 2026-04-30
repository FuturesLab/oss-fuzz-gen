#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "libical/ical.h"
#include <string.h> // Include string.h for strlen

extern "C" {

// Callback function to be used with icalcomponent_foreach_recurrence
void recurrence_callback_5(const icalcomponent *comp, const struct icaltime_span *span, void *data) {
    // This is a placeholder callback function
}

int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Ensure the component is not NULL
    if (component == NULL) {
        return 0;
    }

    // Create start and end time for the recurrence
    struct icaltimetype start_time = icaltime_from_timet_with_zone(time(NULL), 0, NULL);
    struct icaltimetype end_time = icaltime_from_timet_with_zone(time(NULL) + 3600, 0, NULL);

    // Set a valid DTSTART property to the component
    icalcomponent_set_dtstart(component, start_time);

    // Set a RRULE property to the component using the input data
    if (size > 0) {
        // Ensure the input data is null-terminated before converting to string
        char *data_str = (char *)malloc(size + 1);
        if (data_str == NULL) {
            icalcomponent_free(component);
            return 0;
        }
        memcpy(data_str, data, size);
        data_str[size] = '\0'; // Null-terminate the string

        icalproperty *rrule_prop = icalproperty_new_from_string(data_str);
        if (rrule_prop != NULL) {
            icalcomponent_add_property(component, rrule_prop);
        }

        free(data_str); // Free the allocated memory
    }

    // Call the function under test
    icalcomponent_foreach_recurrence(component, start_time, end_time, recurrence_callback_5, NULL);

    // Clean up
    icalcomponent_free(component);

    return 0;
}

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

    LLVMFuzzerTestOneInput_5(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
