#include <stdint.h>
#include <time.h> // For time(NULL)

extern "C" {
    #include <libical/ical.h> // Correct include path for libical
}

extern "C" int LLVMFuzzerTestOneInput_456(const uint8_t *data, size_t size) {
    if (size < sizeof(struct icaldatetimeperiodtype)) {
        return 0; // Not enough data to fill icaldatetimeperiodtype
    }

    // Initialize the icaldatetimeperiodtype structure
    struct icaldatetimeperiodtype dtp;
    dtp.time = icaltime_from_timet_with_zone(time(NULL), 0, NULL);
    dtp.period = icalperiodtype_null_period();

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_rdate(dtp);

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

    LLVMFuzzerTestOneInput_456(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
