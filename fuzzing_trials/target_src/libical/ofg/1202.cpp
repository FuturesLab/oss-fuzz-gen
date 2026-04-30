#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1202(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to extract meaningful values for the struct
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize an icaltimetype structure
    struct icaltimetype time;
    
    // Populate the icaltimetype structure with data
    // Assuming data is structured correctly, otherwise, this needs more careful handling
    time.year = (int)data[0] + 1900; // Year offset to make it more realistic
    time.month = (int)(data[1] % 12) + 1; // Month in range 1-12
    time.day = (int)(data[2] % 31) + 1; // Day in range 1-31
    time.hour = (int)(data[3] % 24); // Hour in range 0-23
    time.minute = (int)(data[4] % 60); // Minute in range 0-59
    time.second = (int)(data[5] % 60); // Second in range 0-59
    time.is_date = data[6] % 2; // Boolean value
    time.is_daylight = data[7] % 2; // Boolean value for daylight saving
    time.zone = NULL; // NULL for simplicity, as zones are complex structures

    // Call the function-under-test
    int day_of_year = icaltime_day_of_year(time);

    // Use the result to avoid compiler optimizations
    volatile int result = day_of_year;
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

    LLVMFuzzerTestOneInput_1202(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
