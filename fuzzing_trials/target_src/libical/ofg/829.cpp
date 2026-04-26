#include <stdint.h>
#include <stddef.h>
#include <string.h> // For memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_829(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for creating a valid icalperiodtype
    if (size < sizeof(struct icalperiodtype)) {
        return 0;
    }

    // Create an icalperiodtype structure from the input data
    struct icalperiodtype period;
    memcpy(&period, data, sizeof(struct icalperiodtype));

    // Use the period in some meaningful way
    // For example, check if the period is valid
    if (icalperiodtype_is_null_period(period)) {
        // Handle the null period case
    } else {
        // Process the period
        const char *period_string = icalperiodtype_as_ical_string(period);
        if (period_string) {
            // Normally you would do something with period_string
            // For fuzzing, we just free it
            icalmemory_free_buffer((void*)period_string);
        }
    }

    // Return 0 to indicate the fuzzer should continue testing
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

    LLVMFuzzerTestOneInput_829(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
