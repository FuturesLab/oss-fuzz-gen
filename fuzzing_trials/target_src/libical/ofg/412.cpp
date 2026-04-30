#include <cstdint>
#include <cstddef> // Include for size_t

// Assuming the enumeration is defined as follows:
extern "C" {
    typedef enum {
        SUNDAY,
        MONDAY,
        TUESDAY,
        WEDNESDAY,
        THURSDAY,
        FRIDAY,
        SATURDAY
    } DW_TAG_enumeration_typeicalrecurrencetype_weekday;

    // Function-under-test
    DW_TAG_enumeration_typeicalrecurrencetype_weekday icalrecurrencetype_day_day_of_week(short day);
}

extern "C" int LLVMFuzzerTestOneInput_412(const uint8_t *data, size_t size) {
    if (size < sizeof(short)) {
        return 0; // Not enough data to form a short
    }

    // Extract a short value from the input data
    short day = *(reinterpret_cast<const short*>(data));

    // Call the function-under-test
    DW_TAG_enumeration_typeicalrecurrencetype_weekday result = icalrecurrencetype_day_day_of_week(day);

    // Use the result in some way (for example, to avoid compiler optimizations removing the call)
    (void)result;

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

    LLVMFuzzerTestOneInput_412(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
