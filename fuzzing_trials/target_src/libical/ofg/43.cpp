#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to create a valid icaltimetype
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Create a dummy icaltimezone object
    icaltimezone *timezone = icaltimezone_get_builtin_timezone("UTC");

    // Use the data to create an icaltimetype
    struct icaltimetype time;
    memcpy(&time, data, sizeof(struct icaltimetype));

    // Initialize the int pointer
    int utc_offset = 0;

    // Call the function-under-test
    int result = icaltimezone_get_utc_offset(timezone, &time, &utc_offset);

    // Use the result and utc_offset to avoid unused variable warnings
    (void)result;
    (void)utc_offset;

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

    LLVMFuzzerTestOneInput_43(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
