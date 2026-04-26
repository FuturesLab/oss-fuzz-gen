#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h> // Include string.h for memcpy

extern "C" {
    // Assuming the icaltime_span structure and icaltime_span_contains function are defined in the project
    typedef struct {
        int64_t start;
        int64_t end;
        int is_busy;
    } icaltime_span;

    // Function under test
    bool icaltime_span_contains(const icaltime_span *span1, const icaltime_span *span2);
}

extern "C" int LLVMFuzzerTestOneInput_341(const uint8_t *data, size_t size) {
    if (size < sizeof(icaltime_span) * 2) {
        return 0; // Not enough data to create two icaltime_span structures
    }

    // Create two icaltime_span structures from the input data
    icaltime_span span1;
    icaltime_span span2;

    // Copy data into the icaltime_span structures
    // Ensure that the data is correctly aligned and non-NULL
    memcpy(&span1, data, sizeof(icaltime_span));
    memcpy(&span2, data + sizeof(icaltime_span), sizeof(icaltime_span));

    // Call the function under test
    bool result = icaltime_span_contains(&span1, &span2);

    // Use the result to avoid any compiler optimizations that might skip the call
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

    LLVMFuzzerTestOneInput_341(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
