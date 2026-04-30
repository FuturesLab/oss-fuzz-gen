#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <libical/ical.h>
#include <cstring> // Include cstring for memcpy

extern "C" {
    #include <libical/ical.h> // Ensure all C headers are wrapped in extern "C"
}

extern "C" int LLVMFuzzerTestOneInput_1354(const uint8_t *data, size_t size) {
    // Ensure the size is large enough to create a valid icalperiodtype
    if (size < sizeof(struct icalperiodtype)) {
        return 0;
    }

    // Create a icalperiodtype from the input data
    struct icalperiodtype period;
    memcpy(&period, data, sizeof(struct icalperiodtype));

    // Call the function-under-test
    bool result = icalperiodtype_is_null_period(period);

    // Use the result in some way to avoid compiler optimizations
    if (result) {
        // Do something if the period is null
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

    LLVMFuzzerTestOneInput_1354(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
