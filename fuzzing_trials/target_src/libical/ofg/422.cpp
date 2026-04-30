#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include the string.h library for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_422(const uint8_t *data, size_t size) {
    // Ensure there's enough data to populate two icaltimetype structures and a timezone
    if (size < 2 * sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize two icaltimetype structures from the input data
    struct icaltimetype time1 = icaltime_null_time();
    struct icaltimetype time2 = icaltime_null_time();

    // Copy data into the icaltimetype structures
    memcpy(&time1, data, sizeof(struct icaltimetype));
    memcpy(&time2, data + sizeof(struct icaltimetype), sizeof(struct icaltimetype));

    // Create a default timezone
    icaltimezone *timezone = icaltimezone_get_utc_timezone();

    // Call the function-under-test
    int result = icaltime_compare_date_only_tz(time1, time2, timezone);

    // Use the result in some way to prevent optimization out
    if (result == 0) {
        return 0;
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

    LLVMFuzzerTestOneInput_422(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
