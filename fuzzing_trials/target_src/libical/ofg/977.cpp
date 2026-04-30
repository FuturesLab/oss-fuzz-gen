#include <stdint.h>
#include <stddef.h>
#include <time.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_977(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to construct a valid icaltimetype
    if (size < sizeof(int) * 6) {
        return 0;
    }

    // Extract values for icaltimetype from the input data
    int year = ((int*)data)[0];
    int month = ((int*)data)[1] % 12 + 1; // Ensure month is between 1 and 12
    int day = ((int*)data)[2] % 31 + 1;   // Ensure day is between 1 and 31
    int hour = ((int*)data)[3] % 24;      // Ensure hour is between 0 and 23
    int minute = ((int*)data)[4] % 60;    // Ensure minute is between 0 and 59
    int second = ((int*)data)[5] % 60;    // Ensure second is between 0 and 59

    // Initialize icaltimetype
    struct icaltimetype time = icaltime_null_time();

    // Set the extracted values
    time.year = year;
    time.month = month;
    time.day = day;
    time.hour = hour;
    time.minute = minute;
    time.second = second;

    // Call the function-under-test
    icalproperty *prop = icalproperty_vanew_lastmodified(time, NULL);

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

    LLVMFuzzerTestOneInput_977(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
