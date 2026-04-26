#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_115(const uint8_t *data, size_t size) {
    // Initialize icalproperty
    icalproperty *prop = icalproperty_new(ICAL_LASTMODIFIED_PROPERTY);
    if (prop == NULL) {
        return 0; // Return if property creation fails
    }

    // Initialize icaltimetype
    struct icaltimetype lastmodified_time;
    lastmodified_time.year = (size > 0) ? data[0] + 1900 : 2022; // Year range: 1900-2155
    lastmodified_time.month = (size > 1) ? (data[1] % 12) + 1 : 1; // Month range: 1-12
    lastmodified_time.day = (size > 2) ? (data[2] % 31) + 1 : 1; // Day range: 1-31
    lastmodified_time.hour = (size > 3) ? data[3] % 24 : 0; // Hour range: 0-23
    lastmodified_time.minute = (size > 4) ? data[4] % 60 : 0; // Minute range: 0-59
    lastmodified_time.second = (size > 5) ? data[5] % 60 : 0; // Second range: 0-59
    lastmodified_time.is_date = 0;
    lastmodified_time.is_daylight = 0; // Assuming no daylight saving time
    lastmodified_time.zone = icaltimezone_get_utc_timezone();

    // Call the function-under-test
    icalproperty_set_lastmodified(prop, lastmodified_time);

    // Clean up
    icalproperty_free(prop);

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

    LLVMFuzzerTestOneInput_115(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
