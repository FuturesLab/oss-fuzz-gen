#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_693(const uint8_t *data, size_t size) {
    // Ensure there's enough data to fill the icaldurationtype structure
    if (size < sizeof(struct icaldurationtype)) {
        return 0;
    }

    // Initialize the icaldurationtype structure
    struct icaldurationtype duration;
    duration.is_neg = data[0] % 2; // Use the first byte for is_neg (0 or 1)
    duration.weeks = data[1];      // Use the second byte for weeks
    duration.days = data[2];       // Use the third byte for days
    duration.hours = data[3];      // Use the fourth byte for hours
    duration.minutes = data[4];    // Use the fifth byte for minutes
    duration.seconds = data[5];    // Use the sixth byte for seconds

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_duration(duration);

    // Clean up the created icalproperty to avoid memory leaks
    if (prop != NULL) {
        icalproperty_free(prop);
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

    LLVMFuzzerTestOneInput_693(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
