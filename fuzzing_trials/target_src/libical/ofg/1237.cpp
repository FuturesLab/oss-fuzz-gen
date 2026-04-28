extern "C" {
    #include <libical/ical.h>
    #include <stdint.h>
    #include <stddef.h>
}

extern "C" int LLVMFuzzerTestOneInput_1237(const uint8_t *data, size_t size) {
    // Ensure there is enough data to initialize icaltimetype
    if (size < sizeof(int) * 6) {
        return 0;
    }

    // Initialize icaltimetype with data
    struct icaltimetype time;
    time.year = (int)data[0];
    time.month = (int)data[1];
    time.day = (int)data[2];
    time.hour = (int)data[3];
    time.minute = (int)data[4];
    time.second = (int)data[5];
    time.is_date = 1; // Set to 1 to indicate it's a date
    // Instead of using is_utc, use zone, which is the correct member for time zone
    time.zone = NULL; // NULL indicates local time

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_maxdate(time);

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

    LLVMFuzzerTestOneInput_1237(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
