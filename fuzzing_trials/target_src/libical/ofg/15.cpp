#include <cstdint>  // Include for uint8_t
#include <cstddef>  // Include for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    // Declare and initialize the icalproperty
    icalproperty *prop = icalproperty_new(ICAL_EXDATE_PROPERTY);
    
    // Declare and initialize the icaltimetype
    struct icaltimetype exdate;
    exdate.year = 2023;  // Set a default valid year
    exdate.month = (size > 0) ? (data[0] % 12) + 1 : 1;  // Ensure month is between 1 and 12
    exdate.day = (size > 1) ? (data[1] % 31) + 1 : 1;    // Ensure day is between 1 and 31
    exdate.hour = (size > 2) ? data[2] % 24 : 0;         // Ensure hour is between 0 and 23
    exdate.minute = (size > 3) ? data[3] % 60 : 0;       // Ensure minute is between 0 and 59
    exdate.second = (size > 4) ? data[4] % 60 : 0;       // Ensure second is between 0 and 59
    exdate.is_date = 0;  // Set to false, indicating it includes time
    exdate.zone = icaltimezone_get_utc_timezone(); // Set to UTC timezone

    // Call the function-under-test
    icalproperty_set_exdate(prop, exdate);

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

    LLVMFuzzerTestOneInput_15(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
