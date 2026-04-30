#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_273(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid string
    if (size < 1) {
        return 0;
    }

    // Initialize a memory context
    icaltimezone *timezone = icaltimezone_new();

    // Ensure timezone is not NULL
    if (timezone == NULL) {
        return 0;
    }

    // Call the function-under-test
    const char *tzid = icaltimezone_get_tzid(timezone);

    // Use the result in some way to prevent compiler optimizations
    if (tzid != NULL) {
        // Print the tzid for debugging purposes (remove in production)
        // printf("Timezone ID: %s\n", tzid);
    }

    // Free the allocated timezone
    icaltimezone_free(timezone, 1);

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

    LLVMFuzzerTestOneInput_273(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
