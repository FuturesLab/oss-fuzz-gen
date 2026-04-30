#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <libical/ical.h>
#include <cstring> // Include the C++ header for memcpy

extern "C" {
    // Include necessary C headers and functions here
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_328(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create an icaltimetype struct
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize an icaltimetype structure with data from the fuzzer
    struct icaltimetype time;
    // Copy data into the icaltimetype structure
    memcpy(&time, data, sizeof(struct icaltimetype));

    // Call the function-under-test
    bool is_date = icaltime_is_date(time);

    // Use the result in some way to prevent compiler optimizations
    if (is_date) {
        // Do something if it's a date
    } else {
        // Do something else if it's not a date
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

    LLVMFuzzerTestOneInput_328(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
