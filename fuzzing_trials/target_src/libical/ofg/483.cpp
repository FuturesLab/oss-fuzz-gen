#include <stdint.h>
#include <stddef.h>
#include <time.h> // Include time.h for time-related functions

extern "C" {
    #include <libical/ical.h> // Correctly include the libical header within extern "C"
}

extern "C" int LLVMFuzzerTestOneInput_483(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a valid icalproperty
    if (size < 1) {
        return 0;
    }

    // Create an icalproperty object
    icalproperty *property = icalproperty_new(ICAL_DTSTART_PROPERTY);

    // Use the input data to create a more dynamic value for the property
    struct icaltimetype time_value;
    time_value.year = 2020 + data[0]; // Use the first byte to influence the year
    time_value.month = (data[0] % 12) + 1; // Use the first byte to influence the month
    time_value.day = (data[0] % 28) + 1; // Use the first byte to influence the day
    time_value.hour = (data[0] % 24); // Use the first byte to influence the hour
    time_value.minute = (data[0] % 60); // Use the first byte to influence the minute
    time_value.second = (data[0] % 60); // Use the first byte to influence the second
    time_value.is_date = 0;
    time_value.is_daylight = 0;
    time_value.zone = icaltimezone_get_utc_timezone();

    icalvalue *value = icalvalue_new_datetime(time_value);
    icalproperty_set_value(property, value);

    // Call the function-under-test
    struct icaltimetype dtstart = icalproperty_get_dtstart(property);

    // Clean up
    icalproperty_free(property);

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

    LLVMFuzzerTestOneInput_483(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
