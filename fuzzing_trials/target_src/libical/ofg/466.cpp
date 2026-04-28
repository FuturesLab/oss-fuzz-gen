#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_466(const uint8_t *data, size_t size) {
    // Ensure there is enough data to fill the struct icaltimetype
    if (size < sizeof(struct icaltimetype) + sizeof(int)) {
        return 0;
    }

    // Initialize the icaltimetype structure
    struct icaltimetype time;
    time.year = (int16_t)data[0] | ((int16_t)data[1] << 8);
    time.month = (int8_t)data[2] % 12 + 1;  // Ensure month is between 1 and 12
    time.day = (int8_t)data[3] % 31 + 1;    // Ensure day is between 1 and 31
    time.hour = (int8_t)data[4] % 24;       // Ensure hour is between 0 and 23
    time.minute = (int8_t)data[5] % 60;     // Ensure minute is between 0 and 59
    time.second = (int8_t)data[6] % 60;     // Ensure second is between 0 and 59
    time.is_date = data[7] % 2;             // Ensure is_date is 0 or 1
    time.is_daylight = data[8] % 2;         // Ensure is_daylight is 0 or 1
    time.zone = NULL;                       // Set zone to NULL

    // Extract the integer for the second parameter
    int week_start = (int)data[9] % 7;      // Ensure week_start is between 0 and 6

    // Call the function-under-test
    int result = icaltime_start_doy_week(time, week_start);

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

    LLVMFuzzerTestOneInput_466(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
