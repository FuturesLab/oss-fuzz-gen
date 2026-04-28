#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_525(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract two integers
    if (size < 2 * sizeof(int)) {
        return 0;
    }

    // Extract two integers from the input data
    int day_of_year = *(reinterpret_cast<const int*>(data));
    int year = *(reinterpret_cast<const int*>(data + sizeof(int)));

    // Call the function-under-test
    struct icaltimetype result = icaltime_from_day_of_year(day_of_year, year);

    // Return 0 to indicate successful execution
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

    LLVMFuzzerTestOneInput_525(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
