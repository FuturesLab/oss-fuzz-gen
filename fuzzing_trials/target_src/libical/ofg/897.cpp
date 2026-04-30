#include <stdint.h>
#include <stdbool.h>
#include <libical/ical.h>  // Assuming libical is the library providing icaldurationtype
#include <cstring>  // Include cstring for memcpy

extern "C" {
    bool icaldurationtype_is_bad_duration(struct icaldurationtype);
}

extern "C" int LLVMFuzzerTestOneInput_897(const uint8_t *data, size_t size) {
    if (size < sizeof(struct icaldurationtype)) {
        return 0;  // Not enough data to fill the structure
    }

    struct icaldurationtype duration;

    // Copy data into the structure, ensuring no overflow
    memcpy(&duration, data, sizeof(struct icaldurationtype));

    // Call the function-under-test
    bool result = icaldurationtype_is_bad_duration(duration);

    // Use the result to prevent the compiler from optimizing the call away
    volatile bool prevent_optimization = result;

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

    LLVMFuzzerTestOneInput_897(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
