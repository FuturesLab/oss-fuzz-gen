#include <stdint.h>
#include <stdbool.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h> // Corrected include path for libical
}

extern "C" int LLVMFuzzerTestOneInput_1077(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to extract two icaltimetype structures and a boolean
    if (size < sizeof(struct icaltimetype) * 2 + sizeof(bool)) {
        return 0;
    }

    // Initialize two icaltimetype structures from the input data
    struct icaltimetype start_time;
    struct icaltimetype end_time;

    // Copy data into the icaltimetype structures
    memcpy(&start_time, data, sizeof(struct icaltimetype));
    memcpy(&end_time, data + sizeof(struct icaltimetype), sizeof(struct icaltimetype));

    // Extract a boolean value from the input data
    bool is_busy = *(bool *)(data + sizeof(struct icaltimetype) * 2);

    // Call the function-under-test
    struct icaltime_span span = icaltime_span_new(start_time, end_time, is_busy);

    // Use the span variable to avoid compiler optimizations removing it
    if (span.is_busy != is_busy) {
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

    LLVMFuzzerTestOneInput_1077(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
