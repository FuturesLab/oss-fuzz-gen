#include <stdint.h>
#include <stdlib.h>
#include <libical/ical.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_114(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract values for icaltimetype
    if (size < 7) {
        return 0;
    }

    // Create a new icalproperty
    icalproperty *prop = icalproperty_new(ICAL_LASTMODIFIED_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Extract values from data for icaltimetype
    struct icaltimetype lastmodified;
    lastmodified.year = (int16_t)data[0] + ((int16_t)data[1] << 8);
    lastmodified.month = data[2] % 12 + 1;  // Ensure month is between 1 and 12
    lastmodified.day = data[3] % 31 + 1;    // Ensure day is between 1 and 31
    lastmodified.hour = data[4] % 24;       // Ensure hour is between 0 and 23
    lastmodified.minute = data[5] % 60;     // Ensure minute is between 0 and 59
    lastmodified.second = data[6] % 60;     // Ensure second is between 0 and 59
    lastmodified.is_date = 0;               // Set to 0 for date-time
    lastmodified.zone = icaltimezone_get_utc_timezone(); // Set to UTC timezone

    // Call the function-under-test
    icalproperty_set_lastmodified(prop, lastmodified);

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

    LLVMFuzzerTestOneInput_114(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
