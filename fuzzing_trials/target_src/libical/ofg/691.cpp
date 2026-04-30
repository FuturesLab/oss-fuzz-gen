#include <stdint.h>
#include <stdlib.h>
#include <time.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_691(const uint8_t *data, size_t size) {
    // Declare and initialize the icalproperty pointer
    icalproperty *prop = icalproperty_new(ICAL_DTEND_PROPERTY);

    // Check if the size is sufficient to extract values for icaltimetype
    if (size < sizeof(int) * 6) {
        icalproperty_free(prop);
        return 0;
    }

    // Extract values for icaltimetype from the data
    int year = (int)data[0] + 1900; // Year from 1900-2555
    int month = (int)data[1] % 12 + 1; // Month from 1-12
    int day = (int)data[2] % 31 + 1; // Day from 1-31
    int hour = (int)data[3] % 24; // Hour from 0-23
    int minute = (int)data[4] % 60; // Minute from 0-59
    int second = (int)data[5] % 60; // Second from 0-59

    // Create an icaltimetype instance
    struct icaltimetype dtend_time = icaltime_from_timet_with_zone(
        time(NULL), 0, NULL);
    dtend_time.year = year;
    dtend_time.month = month;
    dtend_time.day = day;
    dtend_time.hour = hour;
    dtend_time.minute = minute;
    dtend_time.second = second;

    // Call the function-under-test
    icalproperty_set_dtend(prop, dtend_time);

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

    LLVMFuzzerTestOneInput_691(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
