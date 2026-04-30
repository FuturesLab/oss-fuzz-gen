#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_377(const uint8_t *data, size_t size) {
    // Initialize an icaltimetype structure with some default values
    struct icaltimetype time;
    
    // Ensure the data size is sufficient to assign values
    if (size >= sizeof(int) * 6) {
        // Populate the icaltimetype structure with data
        time.year = ((int *)data)[0];
        time.month = ((int *)data)[1] % 12 + 1; // Ensure month is valid (1-12)
        time.day = ((int *)data)[2] % 31 + 1;   // Ensure day is valid (1-31)
        time.hour = ((int *)data)[3] % 24;      // Ensure hour is valid (0-23)
        time.minute = ((int *)data)[4] % 60;    // Ensure minute is valid (0-59)
        time.second = ((int *)data)[5] % 60;    // Ensure second is valid (0-59)
    } else {
        // Default values if not enough data
        time.year = 2023;
        time.month = 1;
        time.day = 1;
        time.hour = 0;
        time.minute = 0;
        time.second = 0;
    }

    // Call the function under test
    bool is_utc = icaltime_is_utc(time);

    // Use the result in some way to avoid compiler optimizations
    if (is_utc) {
        // Do something if the time is UTC
    } else {
        // Do something if the time is not UTC
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

    LLVMFuzzerTestOneInput_377(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
