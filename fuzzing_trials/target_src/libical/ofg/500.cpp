#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <cstring>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_500(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create two icaltimetype structures
    if (size < 2 * sizeof(struct icaltimetype)) {
        return 0;
    }

    // Create two icaltimetype structures from the input data
    struct icaltimetype time1;
    struct icaltimetype time2;

    // Copy data into the icaltimetype structures
    std::memcpy(&time1, data, sizeof(struct icaltimetype));
    std::memcpy(&time2, data + sizeof(struct icaltimetype), sizeof(struct icaltimetype));

    // Validate and normalize the icaltimetype structures
    if (!icaltime_is_valid_time(time1) || !icaltime_is_valid_time(time2)) {
        return 0;
    }

    time1 = icaltime_normalize(time1);
    time2 = icaltime_normalize(time2);

    // Call the function-under-test
    int result = icaltime_compare_date_only(time1, time2);

    // Optionally, print the result for debugging purposes
    std::cout << "Comparison result: " << result << std::endl;

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

    LLVMFuzzerTestOneInput_500(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
