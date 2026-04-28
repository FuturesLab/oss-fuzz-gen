#include <sys/stat.h>
#include <stdint.h>
#include <string.h> // Include for memcpy
#include <stdlib.h> // Include for malloc and free

extern "C" {
    #include "libical/ical.h" // Include the correct header for libical
}

extern "C" int LLVMFuzzerTestOneInput_501(const uint8_t *data, size_t size) {
    // Declare and initialize the icaltimetype structure
    struct icaltimetype time;

    // Ensure the size is sufficient to fill the structure
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Copy data into the icaltimetype structure
    memcpy(&time, data, sizeof(struct icaltimetype));

    // Set a valid year, month, and day to prevent invalid date issues
    time.year = 2023;
    time.month = 1;
    time.day = 1;

    // Set a valid time zone to prevent null pointer dereference
    time.zone = icaltimezone_get_utc_timezone();

    // Call the function under test
    icaltimezone *timezone = const_cast<icaltimezone *>(icaltime_get_timezone(time));

    // Use the timezone in some way to prevent optimization out
    if (timezone != NULL) {
        // For example, retrieve the timezone ID
        const char *tzid = icaltimezone_get_tzid(timezone);
        (void)tzid; // Suppress unused variable warning
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

    LLVMFuzzerTestOneInput_501(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
