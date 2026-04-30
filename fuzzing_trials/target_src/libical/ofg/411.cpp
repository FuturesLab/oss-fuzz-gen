#include <stdint.h>
#include <stddef.h>

// Assuming the function and enum are defined somewhere in the included headers
extern "C" {
    typedef enum {
        ICAL_RECURRENCE_WEEKDAY_SUNDAY,
        ICAL_RECURRENCE_WEEKDAY_MONDAY,
        ICAL_RECURRENCE_WEEKDAY_TUESDAY,
        ICAL_RECURRENCE_WEEKDAY_WEDNESDAY,
        ICAL_RECURRENCE_WEEKDAY_THURSDAY,
        ICAL_RECURRENCE_WEEKDAY_FRIDAY,
        ICAL_RECURRENCE_WEEKDAY_SATURDAY
    } DW_TAG_enumeration_typeicalrecurrencetype_weekday;

    DW_TAG_enumeration_typeicalrecurrencetype_weekday icalrecurrencetype_day_day_of_week(short day);
}

extern "C" int LLVMFuzzerTestOneInput_411(const uint8_t *data, size_t size) {
    if (size < sizeof(short)) {
        return 0;
    }

    // Extract a short value from the input data
    short day = *(reinterpret_cast<const short*>(data));

    // Call the function-under-test
    DW_TAG_enumeration_typeicalrecurrencetype_weekday result = icalrecurrencetype_day_day_of_week(day);

    // Optionally, use the result in some way (e.g., print, log, etc.)
    // For fuzzing purposes, we generally don't need to do anything with the result

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

    LLVMFuzzerTestOneInput_411(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
