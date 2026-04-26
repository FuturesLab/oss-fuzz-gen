#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_253(const uint8_t *data, size_t size) {
    // Initialize the timezone
    icaltimezone *zone = icaltimezone_get_utc_timezone();

    // Call the function-under-test
    struct icaltimetype current_time = icaltime_current_time_with_zone(zone);

    // Use the result in some way to avoid compiler optimizations removing the call
    if (icaltime_is_valid_time(current_time)) {
        // Do something with the valid time, such as printing or logging
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

    LLVMFuzzerTestOneInput_253(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
