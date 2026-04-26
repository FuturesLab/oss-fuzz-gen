#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

extern "C" {
    #include <libical/icaltime.h>
}

extern "C" int LLVMFuzzerTestOneInput_153(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create two icaltime_span objects
    if (size < 2 * sizeof(icaltime_span)) {
        return 0;
    }

    // Initialize two icaltime_span objects from the input data
    const icaltime_span *span1 = reinterpret_cast<const icaltime_span *>(data);
    const icaltime_span *span2 = reinterpret_cast<const icaltime_span *>(data + sizeof(icaltime_span));

    // Call the function-under-test
    bool result = icaltime_span_contains(span1, span2);

    // Use the result in some way to avoid compiler optimizations removing the call
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

    LLVMFuzzerTestOneInput_153(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
