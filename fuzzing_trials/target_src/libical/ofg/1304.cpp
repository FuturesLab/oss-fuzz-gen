#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include string.h for memcpy and strlen

extern "C" {
    #include <libical/ical.h> // Include the correct path for libical headers
}

extern "C" int LLVMFuzzerTestOneInput_1304(const uint8_t *data, size_t size) {
    // Ensure there is enough data for initializing icaltimetype
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize icaltimetype with data
    struct icaltimetype time;
    memcpy(&time, data, sizeof(struct icaltimetype));

    // Ensure the icaltimetype is valid before using it
    if (!icaltime_is_valid_time(time)) {
        return 0;
    }

    // Call the function under test
    const char *tzid = icaltime_get_tzid(time);

    // Use tzid in some way to prevent any compiler optimizations removing the call
    if (tzid != NULL) {
        // Do something trivial with tzid, like checking its length
        size_t len = strlen(tzid);
        (void)len; // Suppress unused variable warning
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

    LLVMFuzzerTestOneInput_1304(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
