#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1047(const uint8_t *data, size_t size) {
    if (size < sizeof(struct icaltimetype) + sizeof(struct icaldurationtype)) {
        return 0;
    }

    // Initialize icaltimetype and icaldurationtype from the input data
    struct icaltimetype time;
    struct icaldurationtype duration;

    // Copy data into the structures
    memcpy(&time, data, sizeof(struct icaltimetype));
    memcpy(&duration, data + sizeof(struct icaltimetype), sizeof(struct icaldurationtype));

    // Call the function-under-test
    struct icaltimetype result = icalduration_extend(time, duration);

    // Use the result in some way to avoid any compiler optimizations that might skip the function call
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

    LLVMFuzzerTestOneInput_1047(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
