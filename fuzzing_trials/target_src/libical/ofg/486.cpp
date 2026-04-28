#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_486(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to form a valid icaltimetype
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize icaltimetype using the input data
    struct icaltimetype tt;
    tt.year = (int)data[0] + 1900;  // Year from 1900 to 2155
    tt.month = (int)(data[1] % 12) + 1;  // Month from 1 to 12
    tt.day = (int)(data[2] % 31) + 1;  // Day from 1 to 31
    tt.hour = (int)(data[3] % 24);  // Hour from 0 to 23
    tt.minute = (int)(data[4] % 60);  // Minute from 0 to 59
    tt.second = (int)(data[5] % 60);  // Second from 0 to 59
    tt.is_date = (int)(data[6] % 2);  // is_date as boolean
    // Corrected the member name from is_utc to is_daylight
    tt.is_daylight = (int)(data[7] % 2);  // is_daylight as boolean
    tt.zone = NULL;  // Timezone is set to NULL

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_tzuntil(tt);

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

    LLVMFuzzerTestOneInput_486(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
