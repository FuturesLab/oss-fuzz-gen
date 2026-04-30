#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_239(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to extract integers
    if (size < sizeof(int) * 4) {
        return 0;
    }

    // Initialize variables for the function parameters
    struct icaltimetype time = icaltime_null_time();
    const int days = *(const int *)(data);
    const int hours = *(const int *)(data + sizeof(int));
    const int minutes = *(const int *)(data + 2 * sizeof(int));
    const int seconds = *(const int *)(data + 3 * sizeof(int));

    // Call the function under test
    icaltime_adjust(&time, days, hours, minutes, seconds);

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

    LLVMFuzzerTestOneInput_239(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
