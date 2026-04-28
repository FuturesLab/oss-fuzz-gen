#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>  // Include the string.h library for memcpy

extern "C" {
    #include <libical/ical.h>  // Assuming libical is the library providing icaltimetype and icaltime_is_utc
}

extern "C" int LLVMFuzzerTestOneInput_376(const uint8_t *data, size_t size) {
    // Ensure we have enough data to fill an icaltimetype structure
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize an icaltimetype structure with data from the fuzzer
    struct icaltimetype time;
    memcpy(&time, data, sizeof(struct icaltimetype));

    // Call the function-under-test
    bool is_utc = icaltime_is_utc(time);

    // Use the result in some way to avoid compiler optimizations
    (void)is_utc;

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

    LLVMFuzzerTestOneInput_376(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
