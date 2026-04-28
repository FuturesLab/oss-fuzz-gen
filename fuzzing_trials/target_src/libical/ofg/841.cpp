#include <stdint.h>
#include <stdlib.h>
#include <time.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_841(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract meaningful values
    if (size < sizeof(int) * 6) {
        return 0;
    }

    // Initialize icalproperty
    icalproperty *prop = icalproperty_new(ICAL_DTSTAMP_PROPERTY);

    // Extract values for icaltimetype from the input data
    int year = (int)data[0] + 1900; // Year starting from 1900
    int month = (int)data[1] % 12 + 1; // Month between 1 and 12
    int day = (int)data[2] % 31 + 1; // Day between 1 and 31
    int hour = (int)data[3] % 24; // Hour between 0 and 23
    int minute = (int)data[4] % 60; // Minute between 0 and 59
    int second = (int)data[5] % 60; // Second between 0 and 59

    // Construct icaltimetype
    struct icaltimetype dtstamp = icaltime_from_timet_with_zone(time(NULL), 0, NULL);
    dtstamp.year = year;
    dtstamp.month = month;
    dtstamp.day = day;
    dtstamp.hour = hour;
    dtstamp.minute = minute;
    dtstamp.second = second;
    dtstamp.is_date = 0; // Ensure it's a date-time

    // Call the function-under-test
    icalproperty_set_dtstamp(prop, dtstamp);

    // Clean up
    icalproperty_free(prop);

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

    LLVMFuzzerTestOneInput_841(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
