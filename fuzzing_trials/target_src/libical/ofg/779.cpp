#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include this for memcpy

extern "C" {
    #include <libical/ical.h> // Assuming the correct path for libical headers
}

extern "C" int LLVMFuzzerTestOneInput_779(const uint8_t *data, size_t size) {
    // Ensure there's enough data to work with
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize an icaltimetype structure using the input data
    struct icaltimetype time;
    memcpy(&time, data, sizeof(struct icaltimetype));

    // Create a default timezone
    const icaltimezone *timezone = icaltimezone_get_utc_timezone();

    // Call the function-under-test
    struct icaltimetype result = icaltime_set_timezone(&time, timezone);

    // Use the result in some way to avoid optimizations removing the call
    if (result.is_date) {
        // Do something trivial with the result
        volatile int dummy = result.is_date;
        (void)dummy;
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

    LLVMFuzzerTestOneInput_779(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
