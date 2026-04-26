#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_842(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for creating a valid icaltimetype
    if (size < sizeof(int) * 6) {
        return 0;
    }

    // Initialize an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_DTSTAMP_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Initialize an icaltimetype object using data from the fuzzer
    struct icaltimetype dtstamp;
    dtstamp.year = ((int *)data)[0] % 3000; // Year should be a reasonable value
    dtstamp.month = ((int *)data)[1] % 12 + 1; // Month should be between 1 and 12
    dtstamp.day = ((int *)data)[2] % 31 + 1; // Day should be between 1 and 31
    dtstamp.hour = ((int *)data)[3] % 24; // Hour should be between 0 and 23
    dtstamp.minute = ((int *)data)[4] % 60; // Minute should be between 0 and 59
    dtstamp.second = ((int *)data)[5] % 60; // Second should be between 0 and 59
    dtstamp.is_date = 0; // Ensure it is a date-time
    dtstamp.zone = icaltimezone_get_utc_timezone(); // Set to UTC timezone

    // Call the function-under-test
    icalproperty_set_dtstamp(prop, dtstamp);

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

    LLVMFuzzerTestOneInput_842(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
