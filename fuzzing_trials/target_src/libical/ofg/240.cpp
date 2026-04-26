#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "libical/ical.h"  // Correct path to the header file

    // Function signature from the library
    void icaltime_adjust(struct icaltimetype *, const int, const int, const int, const int);
}

extern "C" int LLVMFuzzerTestOneInput_240(const uint8_t *data, size_t size) {
    // Declare and initialize the parameters for icaltime_adjust
    struct icaltimetype time;
    const int year_adjust = (size > 0) ? data[0] % 10 : 0; // Adjust year by a small value
    const int month_adjust = (size > 1) ? data[1] % 12 : 0; // Adjust month by a small value
    const int day_adjust = (size > 2) ? data[2] % 31 : 0; // Adjust day by a small value
    const int hour_adjust = (size > 3) ? data[3] % 24 : 0; // Adjust hour by a small value

    // Initialize the icaltimetype structure with non-NULL values
    time.year = 2023;
    time.month = 1;
    time.day = 1;
    time.hour = 0;
    time.minute = 0;
    time.second = 0;
    time.is_date = 0;
    time.is_daylight = -1;
    time.zone = icaltimezone_get_utc_timezone();

    // Call the function-under-test
    icaltime_adjust(&time, year_adjust, month_adjust, day_adjust, hour_adjust);

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

    LLVMFuzzerTestOneInput_240(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
