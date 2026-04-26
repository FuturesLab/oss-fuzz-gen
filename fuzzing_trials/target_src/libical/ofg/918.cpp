extern "C" {
    #include <libical/ical.h>
    #include <stdint.h>
    #include <stddef.h>
}

extern "C" int LLVMFuzzerTestOneInput_918(const uint8_t *data, size_t size) {
    // Initialize the icalproperty
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);
    if (!prop) {
        return 0;
    }

    // Initialize the icaltimetype
    struct icaltimetype mindate;
    mindate.year = (size > 0) ? data[0] : 2023; // Ensure non-zero year
    mindate.month = (size > 1) ? data[1] % 12 + 1 : 1; // Month should be 1-12
    mindate.day = (size > 2) ? data[2] % 31 + 1 : 1; // Day should be 1-31
    mindate.hour = (size > 3) ? data[3] % 24 : 0; // Hour should be 0-23
    mindate.minute = (size > 4) ? data[4] % 60 : 0; // Minute should be 0-59
    mindate.second = (size > 5) ? data[5] % 60 : 0; // Second should be 0-59
    mindate.is_date = 0; // Ensure it's a date-time
    mindate.is_daylight = 0; // Assume no daylight saving time
    mindate.zone = icaltimezone_get_utc_timezone();

    // Call the function-under-test
    icalproperty_set_mindate(prop, mindate);

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

    LLVMFuzzerTestOneInput_918(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
