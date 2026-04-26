#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <libical/ical.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_106(const uint8_t *data, size_t size) {
    // Ensure the size is large enough to create an icaltimetype
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Create an icaltimetype from the input data
    struct icaltimetype time;
    memcpy(&time, data, sizeof(struct icaltimetype));

    // Call the function-under-test
    bool is_valid = icaltime_is_valid_time(time);

    // Use the result in some way to prevent optimizations from removing the call
    volatile bool result = is_valid;
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

    LLVMFuzzerTestOneInput_106(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
