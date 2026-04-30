#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "libical/ical.h"

extern "C" {

// Define a callback function that matches the expected signature for the recurrence callback
void recurrence_callback(const icalcomponent *comp,
                         const struct icaltime_span *span,
                         void *data) {
    // This is a placeholder function for the callback
}

int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent
    icalcomponent *comp = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    
    // Create start and end times for the recurrence
    struct icaltimetype start_time = icaltime_from_timet_with_zone(time(NULL), 0, NULL);
    struct icaltimetype end_time = icaltime_from_timet_with_zone(time(NULL) + 3600, 0, NULL);
    
    // Check if the component was created successfully
    if (comp == NULL) {
        return 0;
    }

    // Call the function-under-test
    icalcomponent_foreach_recurrence(comp, start_time, end_time, recurrence_callback, NULL);
    
    // Free the component
    icalcomponent_free(comp);

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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_64(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
