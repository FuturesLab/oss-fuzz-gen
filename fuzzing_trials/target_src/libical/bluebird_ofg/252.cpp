#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_252(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to fill an icaltimetype
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize the icaltimetype structure
    struct icaltimetype dtstamp;
    dtstamp.year = (int)data[0] + 1900;  // Year range: 1900-2255
    dtstamp.month = (int)data[1] % 12 + 1;  // Month range: 1-12
    dtstamp.day = (int)data[2] % 31 + 1;  // Day range: 1-31
    dtstamp.hour = (int)data[3] % 24;  // Hour range: 0-23
    dtstamp.minute = (int)data[4] % 60;  // Minute range: 0-59
    dtstamp.second = (int)data[5] % 60;  // Second range: 0-59
    dtstamp.is_date = 0;  // Assume it's a date-time
    dtstamp.zone = NULL;  // No timezone

    // Call the function under test
    icalproperty *prop = icalproperty_vanew_dtstamp(dtstamp, NULL);

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

    LLVMFuzzerTestOneInput_252(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
