#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_175(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to extract meaningful values
    if (size < sizeof(int) * 6) {
        return 0;
    }

    // Extract values to construct an icaltimetype
    int year = ((int*)data)[0] % 9999;  // Valid year range
    int month = ((int*)data)[1] % 12 + 1; // Valid month range 1-12
    int day = ((int*)data)[2] % 31 + 1;  // Valid day range 1-31
    int hour = ((int*)data)[3] % 24;     // Valid hour range 0-23
    int minute = ((int*)data)[4] % 60;   // Valid minute range 0-59
    int second = ((int*)data)[5] % 60;   // Valid second range 0-59

    // Create an icaltimetype structure
    struct icaltimetype time;
    time.year = year;
    time.month = month;
    time.day = day;
    time.hour = hour;
    time.minute = minute;
    time.second = second;
    time.is_date = 0;  // Set to 0 to indicate it's a date-time, not a date

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

    LLVMFuzzerTestOneInput_175(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
