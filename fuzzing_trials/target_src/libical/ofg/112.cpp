#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_112(const uint8_t *data, size_t size) {
    // Define and initialize two icaltime_span structures
    icaltime_span span1;
    icaltime_span span2;

    // Ensure the size is sufficient to initialize the spans
    if (size < 2 * sizeof(icaltime_span)) {
        return 0;
    }

    // Initialize span1 from the data
    span1.start = *((time_t *)data);
    span1.end = *((time_t *)(data + sizeof(time_t)));
    span1.is_busy = (bool)data[2 * sizeof(time_t)];

    // Initialize span2 from the data
    span2.start = *((time_t *)(data + 2 * sizeof(time_t) + 1));
    span2.end = *((time_t *)(data + 3 * sizeof(time_t) + 1));
    span2.is_busy = (bool)data[4 * sizeof(time_t) + 1];

    // Call the function under test
    bool result = icaltime_span_overlaps(&span1, &span2);

    // Use the result to avoid compiler optimizations
    volatile bool avoid_optimization = result;

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

    LLVMFuzzerTestOneInput_112(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
