#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <libical/ical.h>
#include <string.h> // Include the header for memcpy

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1186(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for initializing icaltimetype
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize an icaltimetype from the input data
    struct icaltimetype ical_time;
    memcpy(&ical_time, data, sizeof(struct icaltimetype));

    // Initialize a default timezone
    const icaltimezone *zone = icaltimezone_get_utc_timezone();

    // Call the function-under-test
    time_t result = icaltime_as_timet_with_zone(ical_time, zone);

    // Use the result to prevent any compiler optimizations that could skip the function call
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

    LLVMFuzzerTestOneInput_1186(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
