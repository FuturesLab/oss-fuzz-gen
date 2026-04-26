#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_1005(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid icaltimetype
    if (size < sizeof(int) * 6) {
        return 0;
    }

    // Extract integers from the input data to create an icaltimetype
    int year = static_cast<int>(data[0] | (data[1] << 8));
    int month = static_cast<int>(data[2] % 12 + 1);  // Ensure month is 1-12
    int day = static_cast<int>(data[3] % 31 + 1);    // Ensure day is 1-31
    int hour = static_cast<int>(data[4] % 24);       // Ensure hour is 0-23
    int minute = static_cast<int>(data[5] % 60);     // Ensure minute is 0-59
    int second = static_cast<int>(data[6] % 60);     // Ensure second is 0-59

    // Create an icaltimetype
    struct icaltimetype exdate_time = icaltime_from_timet_with_zone(
        time(NULL), 0, icaltimezone_get_utc_timezone());

    exdate_time.year = year;
    exdate_time.month = month;
    exdate_time.day = day;
    exdate_time.hour = hour;
    exdate_time.minute = minute;
    exdate_time.second = second;

    // Call the function-under-test
    icalproperty *exdate_property = icalproperty_new_exdate(exdate_time);

    // Clean up
    if (exdate_property != NULL) {
        icalproperty_free(exdate_property);
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

    LLVMFuzzerTestOneInput_1005(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
