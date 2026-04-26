#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h> // Include the correct path for libical headers

    // Ensure the function-under-test and necessary headers are wrapped in extern "C"
    void icalproperty_set_refreshinterval(icalproperty *, struct icaldurationtype);
}

extern "C" int LLVMFuzzerTestOneInput_1131(const uint8_t *data, size_t size) {
    if (size < 5) {
        return 0; // Ensure there's enough data to read five bytes
    }

    // Initialize an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);

    // Prepare an icaldurationtype object
    struct icaldurationtype duration;
    duration.is_neg = 0; // Set a default value
    duration.weeks = data[0] % 10; // Use first byte for weeks
    duration.days = data[1] % 7; // Use second byte for days
    duration.hours = data[2] % 24; // Use third byte for hours
    duration.minutes = data[3] % 60; // Use fourth byte for minutes
    duration.seconds = data[4] % 60; // Use fifth byte for seconds

    // Call the function-under-test
    icalproperty_set_refreshinterval(prop, duration);

    // Clean up
    icalproperty_free(prop);

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

    LLVMFuzzerTestOneInput_1131(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
