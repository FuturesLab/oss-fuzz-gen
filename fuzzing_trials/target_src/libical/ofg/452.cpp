#include <cstdint> // Include standard library for uint8_t
#include <cstddef> // Include standard library for size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_452(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid icaldurationtype
    if (size < sizeof(struct icaldurationtype)) {
        return 0;
    }

    // Initialize an icaldurationtype structure
    struct icaldurationtype duration;

    // Use the input data to populate the icaldurationtype fields
    duration.is_neg = data[0] % 2;  // Use the first byte to determine if negative
    duration.weeks = data[1];       // Use the second byte for weeks
    duration.days = data[2];        // Use the third byte for days
    duration.hours = data[3];       // Use the fourth byte for hours
    duration.minutes = data[4];     // Use the fifth byte for minutes
    duration.seconds = data[5];     // Use the sixth byte for seconds

    // Call the function-under-test
    int seconds = icaldurationtype_as_seconds(duration);

    // Optionally, use the result to prevent compiler optimizations
    (void)seconds;

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

    LLVMFuzzerTestOneInput_452(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
