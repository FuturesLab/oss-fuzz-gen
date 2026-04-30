#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1006(const uint8_t *data, size_t size) {
    // Ensure there is enough data to initialize icaltimetype
    if (size < sizeof(int) * 6) {
        return 0;
    }

    // Initialize icaltimetype structure
    struct icaltimetype exdate;

    // Extract values from the data buffer
    exdate.year = (int)data[0] | ((int)data[1] << 8);
    exdate.month = (int)data[2] % 12 + 1; // Ensure month is between 1 and 12
    exdate.day = (int)data[3] % 31 + 1;   // Ensure day is between 1 and 31
    exdate.hour = (int)data[4] % 24;      // Ensure hour is between 0 and 23
    exdate.minute = (int)data[5] % 60;    // Ensure minute is between 0 and 59
    exdate.second = (int)data[6] % 60;    // Ensure second is between 0 and 59
    exdate.is_date = 1;
    exdate.is_daylight = 0;               // Corrected from is_utc to is_daylight
    exdate.zone = NULL;

    // Call the function-under-test
    icalproperty *property = icalproperty_new_exdate(exdate);

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

    LLVMFuzzerTestOneInput_1006(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
