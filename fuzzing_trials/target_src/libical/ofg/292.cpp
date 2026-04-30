#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <libical/ical.h>

extern "C" {
    #include <string.h> // Include string.h for memcpy
}

extern "C" int LLVMFuzzerTestOneInput_292(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create an icaltimetype
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize an icaltimetype structure with data from the input
    struct icaltimetype ical_time;
    memcpy(&ical_time, data, sizeof(struct icaltimetype));

    // Call the function-under-test
    time_t result = icaltime_as_timet(ical_time);

    // Use the result in some way to avoid compiler optimizations
    if (result == (time_t)-1) {
        // Handle the error case
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

    LLVMFuzzerTestOneInput_292(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
