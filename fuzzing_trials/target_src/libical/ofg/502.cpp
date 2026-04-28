#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include this header for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_502(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to fill the icaldurationtype structure
    if (size < sizeof(struct icaldurationtype)) {
        return 0;
    }

    // Initialize the icaldurationtype structure with the provided data
    struct icaldurationtype duration;
    memcpy(&duration, data, sizeof(struct icaldurationtype));

    // Call the function-under-test
    struct icaldurationtype normalized_duration = icaldurationtype_normalize(duration);

    // Use the normalized_duration in some way to prevent optimizations from removing the call
    volatile int dummy = normalized_duration.is_neg;
    (void)dummy;

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

    LLVMFuzzerTestOneInput_502(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
