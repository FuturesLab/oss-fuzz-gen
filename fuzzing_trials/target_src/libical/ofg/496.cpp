#include <cstdint>
#include <cstddef> // Include for size_t

extern "C" {

// Assuming the enumeration type is defined as follows
typedef enum {
    ICAL_RECURRENCE_WEEKDAY_SUNDAY,
    ICAL_RECURRENCE_WEEKDAY_MONDAY,
    ICAL_RECURRENCE_WEEKDAY_TUESDAY,
    ICAL_RECURRENCE_WEEKDAY_WEDNESDAY,
    ICAL_RECURRENCE_WEEKDAY_THURSDAY,
    ICAL_RECURRENCE_WEEKDAY_FRIDAY,
    ICAL_RECURRENCE_WEEKDAY_SATURDAY
} DW_TAG_enumeration_typeicalrecurrencetype_weekday;

// Function signature
short icalrecurrencetype_encode_day(DW_TAG_enumeration_typeicalrecurrencetype_weekday day, int value);

} // extern "C"

extern "C" int LLVMFuzzerTestOneInput_496(const uint8_t *data, size_t size) {
    if (size < 2) return 0; // Ensure there's enough data for both parameters

    // Extract a weekday from the data
    DW_TAG_enumeration_typeicalrecurrencetype_weekday weekday = static_cast<DW_TAG_enumeration_typeicalrecurrencetype_weekday>(data[0] % 7);

    // Extract an integer value from the data
    int value = static_cast<int>(data[1]);

    // Call the function-under-test
    short result = icalrecurrencetype_encode_day(weekday, value);

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

    LLVMFuzzerTestOneInput_496(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
