#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>  // Include this header to define size_t

// Since 'icaltime.h' does not exist, we need to declare the function prototype manually.
// Ensure this is wrapped in extern "C" to maintain C linkage.
extern "C" {
    // Declare the function prototype for the function-under-test
    bool icaltime_is_leap_year(int year);
}

// Fuzzing harness
extern "C" int LLVMFuzzerTestOneInput_159(const uint8_t *data, size_t size) {
    // Ensure there's enough data to form an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Interpret the first few bytes of data as an integer
    int year = *(reinterpret_cast<const int*>(data));

    // Call the function-under-test
    bool is_leap_year = icaltime_is_leap_year(year);

    // Use the result in some way to avoid compiler optimizations
    if (is_leap_year) {
        // Do something if it's a leap year
    } else {
        // Do something if it's not a leap year
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

    LLVMFuzzerTestOneInput_159(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
