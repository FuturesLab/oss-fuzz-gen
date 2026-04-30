#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

extern "C" {
    #include "libical/ical.h"  // Assuming the header file for icalperiodtype is in libical
}

extern "C" int LLVMFuzzerTestOneInput_90(const uint8_t *data, size_t size) {
    struct icalperiodtype period;

    // Initialize the icalperiodtype structure with non-NULL values
    // Assuming icalperiodtype has start and end as icaltimetype and duration as icaldurationtype
    // These are common fields in icalperiodtype, adjust according to the actual structure definition
    if (size < sizeof(struct icalperiodtype)) {
        return 0;
    }

    // Copy data into the period structure
    memcpy(&period, data, sizeof(struct icalperiodtype));

    // Ensure that the fields are initialized with valid values
    // Here we are assuming start and end are icaltimetype and should be initialized accordingly
    period.start.year = 2023;
    period.start.month = 10;
    period.start.day = 1;
    period.start.hour = 12;
    period.start.minute = 0;
    period.start.second = 0;
    period.start.is_date = 0;

    period.end.year = 2023;
    period.end.month = 10;
    period.end.day = 2;
    period.end.hour = 12;
    period.end.minute = 0;
    period.end.second = 0;
    period.end.is_date = 0;

    // Call the function under test
    bool is_valid = icalperiodtype_is_valid_period(period);

    // Optionally, print the result for debugging purposes
    printf("Period is %s\n", is_valid ? "valid" : "invalid");

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

    LLVMFuzzerTestOneInput_90(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
