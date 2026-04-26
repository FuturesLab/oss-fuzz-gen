#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1076(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract two icaltimetype objects and a bool
    if (size < 2 * sizeof(struct icaltimetype) + sizeof(bool)) {
        return 0;
    }

    // Initialize two icaltimetype objects from the input data
    struct icaltimetype start_time = *reinterpret_cast<const struct icaltimetype*>(data);
    struct icaltimetype end_time = *reinterpret_cast<const struct icaltimetype*>(data + sizeof(struct icaltimetype));

    // Extract a boolean value from the input data
    bool is_busy = *reinterpret_cast<const bool*>(data + 2 * sizeof(struct icaltimetype));

    // Call the function-under-test
    struct icaltime_span span = icaltime_span_new(start_time, end_time, is_busy);

    // Use the span in some way to avoid compiler optimizations removing the call
    (void)span;

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

    LLVMFuzzerTestOneInput_1076(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
