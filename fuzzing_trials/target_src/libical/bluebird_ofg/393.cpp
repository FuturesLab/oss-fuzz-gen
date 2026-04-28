#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_393(const uint8_t *data, size_t size) {
    struct icaltriggertype trigger;

    // Ensure the size is enough to fill the struct. Adjust the size check as needed.
    if (size < sizeof(struct icaldurationtype)) {
        return 0;
    }

    // Initialize the icaltriggertype structure with data from the fuzzer input
    // Assuming the structure has a 'duration' field
    struct icaldurationtype duration;
    duration.is_neg = data[0] % 2;
    duration.weeks = data[1];
    duration.days = data[2];
    duration.hours = data[3];
    duration.minutes = data[4];
    duration.seconds = data[5];

    trigger.duration = duration;

    // Call the function-under-test
    bool result = icaltriggertype_is_bad_trigger(trigger);

    // Use the result to avoid compiler optimizations
    (void)result;

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

    LLVMFuzzerTestOneInput_393(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
