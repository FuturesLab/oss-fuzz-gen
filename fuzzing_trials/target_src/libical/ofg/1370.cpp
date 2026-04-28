#include <stdint.h>
#include <stdlib.h>
#include <libical/ical.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1370(const uint8_t *data, size_t size) {
    // Initialize the icalproperty
    icalproperty *prop = icalproperty_new(ICAL_FREEBUSY_PROPERTY);
    if (prop == NULL) return 0;

    // Define a basic icalperiodtype structure
    struct icalperiodtype period;
    
    // Ensure the data size is sufficient to fill the icalperiodtype fields
    if (size < sizeof(struct icalperiodtype)) {
        icalproperty_free(prop);
        return 0;
    }

    // Populate the icalperiodtype fields using the input data
    // Assuming the input data is structured appropriately for this purpose
    period.start = icaltime_from_timet_with_zone((time_t)data[0], 0, NULL);
    period.end = icaltime_from_timet_with_zone((time_t)data[1], 0, NULL);

    // Convert data to a string to use with icaldurationtype_from_string
    char duration_str[12];
    snprintf(duration_str, sizeof(duration_str), "PT%dS", (int)data[2]);
    period.duration = icaldurationtype_from_string(duration_str);

    // Call the function-under-test
    icalproperty_set_freebusy(prop, period);

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

    LLVMFuzzerTestOneInput_1370(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
