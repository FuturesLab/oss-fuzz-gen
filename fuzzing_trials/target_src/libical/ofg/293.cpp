#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>  // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_293(const uint8_t *data, size_t size) {
    // Ensure there is enough data to construct an icaltimetype object
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Create an icaltimetype object from the input data
    struct icaltimetype ical_time;
    memcpy(&ical_time, data, sizeof(struct icaltimetype));

    // Ensure that the icaltimetype object is initialized with valid values
    ical_time.is_date = 0; // Set to 0 or 1 based on your testing needs

    // Call the function-under-test
    time_t result = icaltime_as_timet(ical_time);

    // Use the result to prevent compiler optimizations from removing the call
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

    LLVMFuzzerTestOneInput_293(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
