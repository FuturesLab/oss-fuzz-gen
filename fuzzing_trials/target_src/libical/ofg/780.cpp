#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_780(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    icaltimetype time;
    icaltimezone *timezone;

    // Initialize the icaltimetype structure with some default values
    time.year = 2023;
    time.month = 10;
    time.day = 1;
    time.hour = 12;
    time.minute = 0;
    time.second = 0;
    time.is_date = 0;
    time.is_daylight = 0;
    time.zone = NULL;

    // Create a timezone using libical functions
    timezone = icaltimezone_get_builtin_timezone("UTC");

    // Call the function-under-test
    icaltimetype result = icaltime_set_timezone(&time, timezone);

    // Use the result in some way to avoid compiler optimizations removing the call
    if (result.zone != NULL) {
        // Do something trivial with the result
        (void)icaltimezone_get_tzid(const_cast<icaltimezone*>(result.zone));
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

    LLVMFuzzerTestOneInput_780(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
