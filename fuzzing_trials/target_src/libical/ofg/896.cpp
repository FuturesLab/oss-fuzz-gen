#include <stdint.h>
#include <stdbool.h>
#include <libical/ical.h> // Assuming libical is the library providing icaldurationtype

extern "C" {
    // Function signature from the library
    bool icaldurationtype_is_bad_duration(struct icaldurationtype);
}

extern "C" int LLVMFuzzerTestOneInput_896(const uint8_t *data, size_t size) {
    struct icaldurationtype duration;

    // Initialize the icaldurationtype fields with non-zero values
    // to ensure none of them are NULL or zero.
    duration.is_neg = (size > 0) ? (data[0] % 2) : 0;
    duration.weeks = (size > 1) ? data[1] : 1;
    duration.days = (size > 2) ? data[2] : 1;
    duration.hours = (size > 3) ? data[3] : 1;
    duration.minutes = (size > 4) ? data[4] : 1;
    duration.seconds = (size > 5) ? data[5] : 1;

    // Call the function-under-test
    bool result = icaldurationtype_is_bad_duration(duration);

    // Return 0 to indicate successful execution of the fuzzer
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

    LLVMFuzzerTestOneInput_896(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
