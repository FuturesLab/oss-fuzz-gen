#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>
#include <cstring> // Include for memcpy

extern "C" {
    int icaltime_start_doy_week(const struct icaltimetype tt, int fdow);
}

extern "C" int LLVMFuzzerTestOneInput_467(const uint8_t *data, size_t size) {
    if (size < sizeof(struct icaltimetype) + sizeof(int)) {
        return 0; // Not enough data to construct inputs
    }

    // Extract icaltimetype from the data
    struct icaltimetype tt;
    memcpy(&tt, data, sizeof(struct icaltimetype));

    // Extract the integer for fdow (first day of the week)
    int fdow;
    memcpy(&fdow, data + sizeof(struct icaltimetype), sizeof(int));

    // Call the function-under-test
    icaltime_start_doy_week(tt, fdow);

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

    LLVMFuzzerTestOneInput_467(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
