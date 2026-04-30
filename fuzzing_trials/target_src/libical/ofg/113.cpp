#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_113(const uint8_t *data, size_t size) {
    // Ensure there is enough data to populate two icaltime_span structures
    if (size < sizeof(icaltime_span) * 2) {
        return 0;
    }

    // Initialize two icaltime_span structures
    icaltime_span span1;
    icaltime_span span2;

    // Populate the spans with data
    const icaltime_span *data_span = (const icaltime_span *)data;
    span1 = data_span[0];
    span2 = data_span[1];

    // Call the function-under-test
    bool result = icaltime_span_overlaps(&span1, &span2);

    // Use the result to prevent the compiler from optimizing away the call
    volatile bool prevent_optimization = result;
    (void)prevent_optimization;

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

    LLVMFuzzerTestOneInput_113(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
