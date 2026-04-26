#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
    // Ensure there's enough data for the test
    if (size < sizeof(struct icaltimetype) + sizeof(int)) {
        return 0;
    }

    // Initialize a timezone object
    icaltimezone *timezone = icaltimezone_get_builtin_timezone("UTC");
    if (!timezone) {
        return 0;
    }

    // Extract icaltimetype from data
    struct icaltimetype time;
    memcpy(&time, data, sizeof(struct icaltimetype));

    // Ensure the time values are within valid ranges
    time.year = time.year % 9999;  // Limit year to a reasonable range
    time.month = (time.month % 12) + 1;  // Ensure month is 1-12
    time.day = (time.day % 31) + 1;  // Ensure day is 1-31
    time.hour = time.hour % 24;  // Ensure hour is 0-23
    time.minute = time.minute % 60;  // Ensure minute is 0-59
    time.second = time.second % 60;  // Ensure second is 0-59

    // Initialize an integer for the UTC offset
    int utc_offset = 0;

    // Call the function-under-test
    int offset = icaltimezone_get_utc_offset(timezone, &time, &utc_offset);

    // Use the result to prevent optimization out
    (void)offset;

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

    LLVMFuzzerTestOneInput_44(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
