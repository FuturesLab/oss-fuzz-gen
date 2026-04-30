#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_635(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a valid icaldatetimeperiodtype
    if (size < sizeof(struct icaltimetype) * 2) {
        return 0;
    }

    // Initialize icalproperty
    icalproperty *prop = icalproperty_new(ICAL_RDATE_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Extract start and end time from the input data
    struct icaltimetype start_time = icaltime_from_timet_with_zone(
        *((time_t *)data), 0, NULL);
    struct icaltimetype end_time = icaltime_from_timet_with_zone(
        *((time_t *)(data + sizeof(struct icaltimetype))), 0, NULL);

    // Create icaldatetimeperiodtype
    struct icaldatetimeperiodtype dtp;
    dtp.time = start_time;
    dtp.period.end = end_time;

    // Call the function under test
    icalproperty_set_rdate(prop, dtp);

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

    LLVMFuzzerTestOneInput_635(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
