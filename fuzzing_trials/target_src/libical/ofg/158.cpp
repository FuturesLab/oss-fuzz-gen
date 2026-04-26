#include <stdint.h>
#include <stdbool.h>
#include <stddef.h> // Include this header to define size_t

extern "C" {
    // Function-under-test declaration
    bool icaltime_is_leap_year(const int year);
}

extern "C" int LLVMFuzzerTestOneInput_158(const uint8_t *data, size_t size) {
    if (size < sizeof(int)) {
        return 0; // Not enough data to form an integer
    }

    // Interpret the first 4 bytes of data as an integer
    int year = *(reinterpret_cast<const int*>(data));

    // Call the function-under-test
    bool is_leap_year = icaltime_is_leap_year(year);

    // Optionally, you can use the result in some way to avoid compiler optimizations
    (void)is_leap_year; // Suppress unused variable warning

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

    LLVMFuzzerTestOneInput_158(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
