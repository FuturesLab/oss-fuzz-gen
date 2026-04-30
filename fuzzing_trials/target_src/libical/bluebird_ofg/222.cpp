#include <string.h>
#include <sys/stat.h>
#include <cstdint>  // Include for uint8_t
#include <cstddef>  // Include for size_t
#include <cstring>  // Include for memcpy

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_222(const uint8_t *data, size_t size) {
    if (size < sizeof(struct icalrecurrencetype)) {
        return 0;
    }

    struct icalrecurrencetype recurrence;
    memcpy(&recurrence, data, sizeof(struct icalrecurrencetype));

    // Ensure that the recurrence type fields have valid values
    recurrence.freq = ICAL_SECONDLY_RECURRENCE;
    recurrence.interval = 1;
    recurrence.count = 1;
    recurrence.until = icaltime_null_time();

    // Call the function under test
    icalproperty *property = icalproperty_vanew_rrule(&recurrence, nullptr);

    // Clean up
    if (property != nullptr) {
        icalproperty_free(property);
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

    LLVMFuzzerTestOneInput_222(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
