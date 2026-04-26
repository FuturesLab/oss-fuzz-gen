#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Create an icaltimetype from the input data
    struct icaltimetype dtstamp;
    if (size >= sizeof(struct icaltimetype)) {
        // Use the input data to initialize the icaltimetype
        dtstamp.year = ((int16_t *)data)[0];
        dtstamp.month = ((int8_t *)data)[2] % 12 + 1; // Ensure month is 1-12
        dtstamp.day = ((int8_t *)data)[3] % 31 + 1;   // Ensure day is 1-31
        dtstamp.hour = ((int8_t *)data)[4] % 24;      // Ensure hour is 0-23
        dtstamp.minute = ((int8_t *)data)[5] % 60;    // Ensure minute is 0-59
        dtstamp.second = ((int8_t *)data)[6] % 60;    // Ensure second is 0-59
        dtstamp.is_date = 0;                          // Set to 0 for date-time
        dtstamp.zone = icaltimezone_get_utc_timezone(); // Set the timezone to UTC
    } else {
        // Use default values if input data is insufficient
        dtstamp = icaltime_current_time_with_zone(icaltimezone_get_utc_timezone());
    }

    // Call the function-under-test
    icalcomponent_set_dtstamp(component, dtstamp);

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

    LLVMFuzzerTestOneInput_58(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
