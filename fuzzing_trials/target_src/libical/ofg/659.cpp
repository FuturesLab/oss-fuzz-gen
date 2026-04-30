#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_659(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a valid icaldurationtype
    if (size < sizeof(struct icaldurationtype)) {
        return 0;
    }

    // Initialize an icaldurationtype structure
    struct icaldurationtype duration;
    duration.is_neg = (int)data[0] % 2; // Use first byte for is_neg
    duration.weeks = (int)data[1];      // Use second byte for weeks
    duration.days = (int)data[2];       // Use third byte for days
    duration.hours = (int)data[3];      // Use fourth byte for hours
    duration.minutes = (int)data[4];    // Use fifth byte for minutes
    duration.seconds = (int)data[5];    // Use sixth byte for seconds

    // Call the function-under-test
    icalproperty *prop = icalproperty_vanew_duration(duration, NULL);

    // Clean up
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

    LLVMFuzzerTestOneInput_659(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
