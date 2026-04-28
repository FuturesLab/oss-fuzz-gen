#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_600(const uint8_t *data, size_t size) {
    // Initialize an icalrecurrencetype structure with some default values.
    struct icalrecurrencetype recurrence;
    recurrence.freq = ICAL_DAILY_RECURRENCE;
    recurrence.interval = 1;
    recurrence.count = 10;
    recurrence.until = icaltime_null_time();
    recurrence.week_start = ICAL_SUNDAY_WEEKDAY;

    // Call the function-under-test with the initialized recurrence structure.
    icalproperty *prop = icalproperty_new_rrule(&recurrence);

    // Clean up the created icalproperty object to avoid memory leaks.
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

    LLVMFuzzerTestOneInput_600(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
