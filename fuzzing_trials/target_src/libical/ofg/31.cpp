#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>
#include <string.h> // Include for memcpy

extern "C" {
    // Include necessary C headers and functions
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    // Ensure that the input data is large enough to fill the icaltimetype structure.
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize an icaltimetype structure with data from the input.
    struct icaltimetype time;
    memcpy(&time, data, sizeof(struct icaltimetype));

    // Call the function-under-test.
    char *result = icaltime_as_ical_string_r(time);

    // Free the result if it's not NULL.
    if (result != NULL) {
        icalmemory_free_buffer(result);
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

    LLVMFuzzerTestOneInput_31(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
