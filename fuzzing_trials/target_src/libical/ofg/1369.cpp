#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h> // Correct include path for libical

    // Function signature
    void icalproperty_set_freebusy(icalproperty *, struct icalperiodtype);
}

extern "C" int LLVMFuzzerTestOneInput_1369(const uint8_t *data, size_t size) {
    if (size < sizeof(struct icalperiodtype)) {
        return 0; // Not enough data to construct icalperiodtype
    }

    // Initialize icalproperty
    icalproperty *property = icalproperty_new(ICAL_FREEBUSY_PROPERTY);
    if (property == NULL) {
        return 0; // Failed to create icalproperty
    }

    // Initialize icalperiodtype
    struct icalperiodtype period;
    period.start = icaltime_from_timet_with_zone(0, 0, NULL);
    period.end = icaltime_from_timet_with_zone(0, 0, NULL);
    period.duration = icaldurationtype_null_duration();

    // Copy data into period (ensuring no overflow)
    memcpy(&period, data, sizeof(struct icalperiodtype));

    // Call the function-under-test
    icalproperty_set_freebusy(property, period);

    // Free the icalproperty
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

    LLVMFuzzerTestOneInput_1369(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
