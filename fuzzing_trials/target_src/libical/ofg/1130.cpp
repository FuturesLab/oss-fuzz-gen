#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1130(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract meaningful data
    if (size < sizeof(int) * 6) {
        return 0;
    }

    // Initialize an icalproperty object
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Extract values for icaldurationtype from the data
    int weeks = (int)data[0];
    int days = (int)data[1];
    int hours = (int)data[2];
    int minutes = (int)data[3];
    int seconds = (int)data[4];
    int is_neg = (int)data[5];

    // Initialize an icaldurationtype object
    struct icaldurationtype duration;
    duration.weeks = weeks;
    duration.days = days;
    duration.hours = hours;
    duration.minutes = minutes;
    duration.seconds = seconds;
    duration.is_neg = is_neg;

    // Call the function-under-test
    icalproperty_set_refreshinterval(property, duration);

    // Clean up
    icalproperty_free(property);

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

    LLVMFuzzerTestOneInput_1130(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
