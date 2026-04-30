#include <cstdint>  // Include standard library for uint8_t
#include <cstddef>  // Include standard library for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_177(const uint8_t *data, size_t size) {
    // Declare and initialize the icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Create an icaltimetype structure with non-NULL values
    struct icaltimetype dtstart;
    dtstart.year = 2023;  // Example year
    dtstart.month = 10;   // Example month
    dtstart.day = 15;     // Example day
    dtstart.hour = 10;    // Example hour
    dtstart.minute = 30;  // Example minute
    dtstart.second = 0;   // Example second
    dtstart.is_date = 0;  // Example flag for datetime
    dtstart.zone = icaltimezone_get_utc_timezone(); // Use UTC timezone

    // Call the function-under-test
    icalcomponent_set_dtstart(component, dtstart);

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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_177(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
