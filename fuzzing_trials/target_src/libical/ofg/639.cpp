#include <cstddef>  // For size_t
#include <cstdint>  // For uint8_t
#include <cstring>  // For strlen

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_639(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icaltimezone *utc_timezone = icaltimezone_get_utc_timezone();

    // Use the returned timezone object in some way to ensure it is not optimized away
    if (utc_timezone != NULL) {
        const char *tzid = icaltimezone_get_tzid(utc_timezone);
        if (tzid != NULL) {
            // Just a simple operation to use the tzid
            size_t tzid_length = strlen(tzid);
            (void)tzid_length;  // Suppress unused variable warning
        }
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

    LLVMFuzzerTestOneInput_639(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
