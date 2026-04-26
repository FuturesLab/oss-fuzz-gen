#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy

extern "C" {
    // Include the necessary C headers and function declarations
    #include <libical/ical.h> // Assuming the correct path for ical.h
    struct icaltimetype icaltime_normalize(const struct icaltimetype);
}

extern "C" int LLVMFuzzerTestOneInput_1305(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a struct icaltimetype
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Create a struct icaltimetype from the input data
    struct icaltimetype time;
    memcpy(&time, data, sizeof(struct icaltimetype));

    // Call the function-under-test
    struct icaltimetype normalized_time = icaltime_normalize(time);

    // Use normalized_time to prevent compiler optimizations
    // This is a no-op but ensures the variable is used
    if (normalized_time.is_date) {
        return 1;
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

    LLVMFuzzerTestOneInput_1305(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
