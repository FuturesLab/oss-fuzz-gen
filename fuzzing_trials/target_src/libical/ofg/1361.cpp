#include <cstdint>
#include <cstddef>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1361(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a valid icalproperty and icalrecurrencetype
    if (size < sizeof(struct icalrecurrencetype)) {
        return 0;
    }

    // Create an icalproperty
    icalproperty *prop = icalproperty_new(ICAL_RRULE_PROPERTY);
    if (!prop) {
        return 0;
    }

    // Initialize an icalrecurrencetype structure from the input data
    struct icalrecurrencetype rrule;
    memcpy(&rrule, data, sizeof(struct icalrecurrencetype));

    // Ensure the icalrecurrencetype fields are valid
    rrule.freq = (icalrecurrencetype_frequency)(rrule.freq % ICAL_NO_RECURRENCE);
    rrule.interval = rrule.interval == 0 ? 1 : rrule.interval; // Interval must be non-zero

    // Call the function-under-test
    icalproperty_set_rrule(prop, &rrule);

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

    LLVMFuzzerTestOneInput_1361(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
