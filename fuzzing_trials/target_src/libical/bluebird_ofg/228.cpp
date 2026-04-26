#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_228(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create two icaltimetype structures
    if (size < sizeof(struct icaltimetype) * 2) {
        return 0;
    }

    // Initialize two icaltimetype structures from the input data
    struct icaltimetype time1, time2;
    memcpy(&time1, data, sizeof(struct icaltimetype));
    memcpy(&time2, data + sizeof(struct icaltimetype), sizeof(struct icaltimetype));

    // Call the function-under-test
    struct icaldurationtype duration = icalduration_from_times(time1, time2);

    // Use the duration in some way to prevent compiler optimizations from removing the call
    (void)duration;

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

    LLVMFuzzerTestOneInput_228(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
