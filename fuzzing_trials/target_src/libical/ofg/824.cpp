#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_824(const uint8_t *data, size_t size) {
    // Initialize necessary structures for the function-under-test
    icaltimezone *timezone = icaltimezone_get_utc_timezone();
    struct icaltimetype time;
    int offset = 0;

    // Ensure that the size is sufficient to fill the icaltimetype structure
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Copy data into the icaltimetype structure
    memcpy(&time, data, sizeof(struct icaltimetype));

    // Call the function-under-test
    int result = icaltimezone_get_utc_offset_of_utc_time(timezone, &time, &offset);

    // Use the result and offset in some way to prevent compiler optimizations from removing the call
    if (result != 0 || offset != 0) {
        // Do something with result and offset if needed
    }

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

    LLVMFuzzerTestOneInput_824(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
