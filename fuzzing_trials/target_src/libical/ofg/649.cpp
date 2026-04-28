extern "C" {
    #include <libical/ical.h>
    #include <stdint.h>
    #include <stddef.h>
}

extern "C" int LLVMFuzzerTestOneInput_649(const uint8_t *data, size_t size) {
    if (size < 7) {
        return 0; // Not enough data to proceed
    }

    // Initialize an icaltimetype structure with some non-NULL values
    struct icaltimetype time;
    time.year = (int16_t)(data[0] | (data[1] << 8));
    time.month = (int8_t)(data[2] % 12 + 1); // Ensure month is between 1 and 12
    time.day = (int8_t)(data[3] % 31 + 1);   // Ensure day is between 1 and 31
    time.hour = (int8_t)(data[4] % 24);      // Ensure hour is between 0 and 23
    time.minute = (int8_t)(data[5] % 60);    // Ensure minute is between 0 and 59
    time.second = (int8_t)(data[6] % 60);    // Ensure second is between 0 and 59
    time.is_date = 0;                        // Set to 0 for a date-time
    time.is_daylight = -1;                   // Unknown daylight savings

    // Call the function-under-test
    icalproperty *prop = icalproperty_vanew_due(time, NULL);

    // Clean up
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

    LLVMFuzzerTestOneInput_649(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
