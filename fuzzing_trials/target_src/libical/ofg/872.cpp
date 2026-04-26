#include <cstdint>  // Include for uint8_t
#include <cstddef>  // Include for size_t
#include <cstring>  // Include for memcpy

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_872(const uint8_t *data, size_t size) {
    // Ensure there's enough data to work with
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize the icaltimetype structure from the input data
    struct icaltimetype input_time;
    memcpy(&input_time, data, sizeof(struct icaltimetype));

    // Create a default timezone for testing
    icaltimezone *timezone = icaltimezone_get_utc_timezone();

    // Call the function under test
    struct icaltimetype result_time = icaltime_convert_to_zone(input_time, timezone);

    // Use the result_time in some way to prevent compiler optimizations from removing the call
    // For example, check if the result is a valid time
    if (icaltime_is_valid_time(result_time)) {
        // Do something with the valid result
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

    LLVMFuzzerTestOneInput_872(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
