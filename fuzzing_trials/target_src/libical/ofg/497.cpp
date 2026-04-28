#include <stdint.h>
#include <stddef.h>

extern "C" {
    // Assuming the enumeration and function are defined in a C library
    typedef enum {
        ICAL_RECURRENCE_SUNDAY,
        ICAL_RECURRENCE_MONDAY,
        ICAL_RECURRENCE_TUESDAY,
        ICAL_RECURRENCE_WEDNESDAY,
        ICAL_RECURRENCE_THURSDAY,
        ICAL_RECURRENCE_FRIDAY,
        ICAL_RECURRENCE_SATURDAY
    } DW_TAG_enumeration_typeicalrecurrencetype_weekday;

    short icalrecurrencetype_encode_day(DW_TAG_enumeration_typeicalrecurrencetype_weekday day, int value);
}

extern "C" int LLVMFuzzerTestOneInput_497(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0; // Not enough data to proceed
    }

    // Use the first byte to determine the weekday
    DW_TAG_enumeration_typeicalrecurrencetype_weekday day = 
        static_cast<DW_TAG_enumeration_typeicalrecurrencetype_weekday>(data[0] % 7);

    // Use the second byte as the integer value
    int value = static_cast<int>(data[1]);

    // Call the function-under-test
    icalrecurrencetype_encode_day(day, value);

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

    LLVMFuzzerTestOneInput_497(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
