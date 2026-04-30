#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

extern "C" {
    #include "libical/ical.h"
}

// Function-under-test
extern "C" bool icalperiodtype_is_valid_period(struct icalperiodtype period);

extern "C" int LLVMFuzzerTestOneInput_89(const uint8_t *data, size_t size) {
    // Initialize a struct icalperiodtype with some default values
    struct icalperiodtype period;

    // Ensure the data is large enough to fill the necessary fields
    if (size < sizeof(struct icalperiodtype)) {
        return 0;
    }

    // Fill the period structure with data from the fuzzing input
    memcpy(&period, data, sizeof(struct icalperiodtype));

    // Call the function-under-test
    bool result = icalperiodtype_is_valid_period(period);

    // Use the result to avoid compiler optimizations
    volatile bool avoid_optimization = result;

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

    LLVMFuzzerTestOneInput_89(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
