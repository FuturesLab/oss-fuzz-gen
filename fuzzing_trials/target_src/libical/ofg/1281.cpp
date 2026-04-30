#include <cstdint>
#include <cstdlib>

// Assume the function is declared in an external C library
extern "C" {
    int icaltime_days_in_month(const int month, const int year);
}

extern "C" int LLVMFuzzerTestOneInput_1281(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract two integers
    if (size < 2) {
        return 0;
    }

    // Extract two integers from the input data
    int month = static_cast<int>(data[0] % 12 + 1); // Ensure month is between 1 and 12
    int year = static_cast<int>(data[1] + 1900);    // Offset year to a reasonable range

    // Call the function under test
    int days = icaltime_days_in_month(month, year);

    // Use the result in some way to prevent compiler optimizations from removing the call
    volatile int result = days;
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

    LLVMFuzzerTestOneInput_1281(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
