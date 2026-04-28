#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_107(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to fill the icaltimetype structure
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Create and initialize a icaltimetype structure from the input data
    struct icaltimetype time;
    memcpy(&time, data, sizeof(struct icaltimetype));

    // Call the function-under-test
    bool result = icaltime_is_valid_time(time);

    // Use the result in some way to prevent optimization out
    if (result) {
        // Do something if the time is valid
    } else {
        // Do something else if the time is invalid
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

    LLVMFuzzerTestOneInput_107(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
