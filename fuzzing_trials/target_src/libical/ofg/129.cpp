#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h> // Ensure that libical is installed and available

extern "C" {
    int icaldurationtype_as_utc_seconds(struct icaldurationtype duration);
}

extern "C" int LLVMFuzzerTestOneInput_129(const uint8_t *data, size_t size) {
    if (size < sizeof(struct icaldurationtype)) {
        return 0; // Not enough data to fill a icaldurationtype structure
    }

    struct icaldurationtype duration;

    // Initialize the icaldurationtype structure with data
    duration.is_neg = data[0] % 2; // Boolean value
    duration.weeks = data[1];
    duration.days = data[2];
    duration.hours = data[3];
    duration.minutes = data[4];
    duration.seconds = data[5];

    // Call the function-under-test
    int seconds = icaldurationtype_as_utc_seconds(duration);

    // Use the result to prevent the compiler from optimizing the call away
    volatile int use_result = seconds;
    (void)use_result;

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

    LLVMFuzzerTestOneInput_129(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
