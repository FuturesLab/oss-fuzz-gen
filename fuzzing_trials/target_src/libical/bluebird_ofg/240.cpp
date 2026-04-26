#include <string.h>
#include <sys/stat.h>
#include <stdint.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_240(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract values for icaldurationtype
    if (size < sizeof(int) * 7) {
        return 0;
    }

    // Initialize the icaldurationtype structure with values from the data
    struct icaldurationtype duration;
    duration.is_neg = data[0] % 2; // 0 or 1
    duration.weeks = data[1];
    duration.days = data[2];
    duration.hours = data[3];
    duration.minutes = data[4];
    duration.seconds = data[5];

    // Call the function-under-test
    icalproperty *prop = icalproperty_vanew_refreshinterval(duration, NULL);

    // Clean up if necessary
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

    LLVMFuzzerTestOneInput_240(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
