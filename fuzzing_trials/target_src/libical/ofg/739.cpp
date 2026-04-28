#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_739(const uint8_t *data, size_t size) {
    // Ensure we have enough data to create a valid icaltimetype
    if (size < sizeof(int) * 6) {
        return 0;
    }

    // Extract values from the data to create a icaltimetype
    int year = ((int*)data)[0];
    int month = ((int*)data)[1] % 12 + 1; // Ensure month is between 1 and 12
    int day = ((int*)data)[2] % 31 + 1;   // Ensure day is between 1 and 31
    int hour = ((int*)data)[3] % 24;      // Ensure hour is between 0 and 23
    int minute = ((int*)data)[4] % 60;    // Ensure minute is between 0 and 59
    int second = ((int*)data)[5] % 60;    // Ensure second is between 0 and 59

    // Create a icaltimetype with the extracted values
    struct icaltimetype dtend_time = icaltime_from_timet_with_zone(
        time(NULL), 0, NULL);
    dtend_time.year = year;
    dtend_time.month = month;
    dtend_time.day = day;
    dtend_time.hour = hour;
    dtend_time.minute = minute;
    dtend_time.second = second;

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_dtend(dtend_time);

    // Clean up
    if (prop != NULL) {
        icalproperty_free(prop);
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_739(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
