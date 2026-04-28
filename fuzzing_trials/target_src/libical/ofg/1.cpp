#include <stdint.h>
#include <stddef.h>

extern "C" {
    // Include the necessary headers for the function-under-test
    #include "libical/ical.h"  // Assuming the function is declared in this library
}

// Function signature for the function-under-test
extern "C" int icaltime_days_in_year(const int year);

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    // Ensure there is enough data to read an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Interpret the first 4 bytes of data as an integer
    int year = *(reinterpret_cast<const int*>(data));

    // Call the function-under-test with the extracted year
    int days = icaltime_days_in_year(year);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)days;

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

    LLVMFuzzerTestOneInput_1(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
