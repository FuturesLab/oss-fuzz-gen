#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy

// Define a non-null timezone for testing
extern "C" {
    icaltimezone *get_test_timezone() {
        return icaltimezone_get_utc_timezone();
    }
}

extern "C" int LLVMFuzzerTestOneInput_421(const uint8_t *data, size_t size) {
    if (size < sizeof(struct icaltimetype) * 2) {
        return 0; // Not enough data to create two icaltimetype structures
    }

    // Initialize two icaltimetype structures from the input data
    struct icaltimetype time1, time2;
    icaltimezone *tz = get_test_timezone();

    // Copy data into the first icaltimetype structure
    memcpy(&time1, data, sizeof(struct icaltimetype));
    // Copy data into the second icaltimetype structure
    memcpy(&time2, data + sizeof(struct icaltimetype), sizeof(struct icaltimetype));

    // Call the function under test
    int result = icaltime_compare_date_only_tz(time1, time2, tz);

    // Use the result in some way to prevent compiler optimizations from removing the call
    if (result == 0) {
        // Do something trivial
        volatile int x = result;
        (void)x;
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

    LLVMFuzzerTestOneInput_421(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
