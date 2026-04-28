extern "C" {
    #include <libical/ical.h>
    #include <stdint.h>
    #include <stddef.h>
}

extern "C" int LLVMFuzzerTestOneInput_891(const uint8_t *data, size_t size) {
    // Declare and initialize the icaltimetype structure
    struct icaltimetype dtstart;

    // Initialize the icaltimetype fields with non-NULL values
    dtstart.year = (size > 0) ? data[0] % 100 + 1900 : 2023; // Year between 1900 and 1999
    dtstart.month = (size > 1) ? data[1] % 12 + 1 : 1;      // Month between 1 and 12
    dtstart.day = (size > 2) ? data[2] % 28 + 1 : 1;        // Day between 1 and 28
    dtstart.hour = (size > 3) ? data[3] % 24 : 0;           // Hour between 0 and 23
    dtstart.minute = (size > 4) ? data[4] % 60 : 0;         // Minute between 0 and 59
    dtstart.second = (size > 5) ? data[5] % 60 : 0;         // Second between 0 and 59
    dtstart.is_date = 0;                                    // Not a date-only value
    dtstart.zone = NULL;                                    // No time zone

    // Call the function-under-test
    icalproperty *property = icalproperty_new_dtstart(dtstart);

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

    LLVMFuzzerTestOneInput_891(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
