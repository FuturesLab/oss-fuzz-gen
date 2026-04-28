#include <cstdint>  // Include for uint8_t
#include <cstdlib>  // Include for size_t and free
#include <cstring>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_529(const uint8_t *data, size_t size) {
    if (size < sizeof(struct icaldurationtype)) {
        return 0;
    }

    struct icaldurationtype duration;
    memcpy(&duration, data, sizeof(struct icaldurationtype));

    // Ensure the duration fields are within reasonable bounds
    duration.is_neg = duration.is_neg % 2; // Ensure it's either 0 or 1
    duration.weeks = duration.weeks % 53;  // Reasonable number of weeks in a year
    duration.days = duration.days % 31;    // Max days in a month
    duration.hours = duration.hours % 24;  // Max hours in a day
    duration.minutes = duration.minutes % 60; // Max minutes in an hour
    duration.seconds = duration.seconds % 60; // Max seconds in a minute

    // Call the function-under-test
    char *result = icaldurationtype_as_ical_string_r(duration);

    // Free the result if not NULL
    if (result != NULL) {
        free(result);
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

    LLVMFuzzerTestOneInput_529(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
