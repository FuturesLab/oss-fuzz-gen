#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include the header for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_871(const uint8_t *data, size_t size) {
    // Ensure there is enough data to fill the icaltimetype structure
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize the icaltimetype structure from the input data
    struct icaltimetype time;
    memcpy(&time, data, sizeof(struct icaltimetype));

    // Create a dummy timezone for testing
    icaltimezone *timezone = icaltimezone_get_utc_timezone();

    // Call the function-under-test
    struct icaltimetype result = icaltime_convert_to_zone(time, timezone);

    // Use the result to prevent optimizations that remove the call
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

    LLVMFuzzerTestOneInput_871(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
