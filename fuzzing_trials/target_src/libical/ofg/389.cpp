#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_389(const uint8_t *data, size_t size) {
    if (size < sizeof(struct icalperiodtype)) {
        return 0; // Not enough data to form a valid icalperiodtype
    }

    // Create an icalperiodtype from the input data
    struct icalperiodtype period;
    period.start = icaltime_from_string("20230101T000000Z");
    period.end = icaltime_from_string("20230102T000000Z");
    // Use a valid function to initialize the duration
    period.duration = icaldurationtype_from_string("PT0S");

    // Call the function-under-test
    icalproperty *prop = icalproperty_vanew_freebusy(period, NULL);

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

    LLVMFuzzerTestOneInput_389(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
