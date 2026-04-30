#include <string.h>
#include <sys/stat.h>
#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_172(const uint8_t *data, size_t size) {
    // Initialize the icaltimetype structure
    struct icaltimetype tt;
    tt.year = (size > 0) ? data[0] : 2023;  // Use the first byte for year or default to 2023
    tt.month = (size > 1) ? data[1] % 12 + 1 : 1; // Use the second byte for month (1-12)
    tt.day = (size > 2) ? data[2] % 31 + 1 : 1; // Use the third byte for day (1-31)
    tt.hour = (size > 3) ? data[3] % 24 : 0; // Use the fourth byte for hour (0-23)
    tt.minute = (size > 4) ? data[4] % 60 : 0; // Use the fifth byte for minute (0-59)
    tt.second = (size > 5) ? data[5] % 60 : 0; // Use the sixth byte for second (0-59)
    tt.is_date = 0;
    tt.is_daylight = 0;
    tt.zone = icaltimezone_get_utc_timezone();

    // Call the function-under-test
    icalproperty *property = icalproperty_vanew_mindate(tt, NULL);

    // Clean up
    if (property != NULL) {
        icalproperty_free(property);
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

    LLVMFuzzerTestOneInput_172(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
