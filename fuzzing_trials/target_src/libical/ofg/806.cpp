#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_806(const uint8_t *data, size_t size) {
    if (size < sizeof(struct icaltimetype) * 2) {
        return 0; // Not enough data to form two icaltimetype structures
    }

    struct icaltimetype time1, time2;

    // Copy data into time1 and time2, ensuring we do not exceed the input size
    memcpy(&time1, data, sizeof(struct icaltimetype));
    memcpy(&time2, data + sizeof(struct icaltimetype), sizeof(struct icaltimetype));

    // Call the function-under-test
    struct icaldurationtype duration = icalduration_from_times(time1, time2);

    // Use the duration to avoid any compiler optimizations removing the call
    (void)duration;

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

    LLVMFuzzerTestOneInput_806(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
