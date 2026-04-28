#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_1307(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create necessary structures
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize the icaltimetype structure
    struct icaltimetype time;
    time.year = (int)data[0] + 1900; // Year 1900 to 2555
    time.month = (int)(data[1] % 12) + 1; // Month 1 to 12
    time.day = (int)(data[2] % 31) + 1; // Day 1 to 31
    time.hour = (int)(data[3] % 24); // Hour 0 to 23
    time.minute = (int)(data[4] % 60); // Minute 0 to 59
    time.second = (int)(data[5] % 60); // Second 0 to 59
    time.is_date = 0; // Not a date-only value
    time.is_daylight = 0; // Not daylight saving time
    time.zone = NULL; // No specific timezone

    // Create two dummy timezones
    icaltimezone *from_zone = icaltimezone_get_utc_timezone();
    icaltimezone *to_zone = icaltimezone_get_builtin_timezone("America/New_York");

    // Call the function-under-test
    icaltimezone_convert_time(&time, from_zone, to_zone);

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

    LLVMFuzzerTestOneInput_1307(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
