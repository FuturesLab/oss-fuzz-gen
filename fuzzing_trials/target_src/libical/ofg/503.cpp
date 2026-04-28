#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include string.h for memcpy

extern "C" {
    #include <libical/icalduration.h> // Correct include path for icalduration.h

    struct icaldurationtype icaldurationtype_normalize(struct icaldurationtype);
}

extern "C" int LLVMFuzzerTestOneInput_503(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to populate an icaldurationtype struct
    if (size < sizeof(struct icaldurationtype)) {
        return 0;
    }

    // Create an icaldurationtype instance from the input data
    struct icaldurationtype duration;
    memcpy(&duration, data, sizeof(struct icaldurationtype));

    // Call the function-under-test
    struct icaldurationtype normalized_duration = icaldurationtype_normalize(duration);

    // Use the normalized_duration to prevent compiler optimizations
    (void)normalized_duration;

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

    LLVMFuzzerTestOneInput_503(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
