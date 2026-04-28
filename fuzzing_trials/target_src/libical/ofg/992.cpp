#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_992(const uint8_t *data, size_t size) {
    // Initialize a dummy timezone
    icaltimezone *timezone = icaltimezone_new();

    // Ensure the timezone is not NULL
    if (timezone == NULL) {
        return 0;
    }

    // Call the function-under-test
    const char *tz_names = icaltimezone_get_tznames(timezone);

    // Check the result (tz_names should not be NULL)
    if (tz_names != NULL) {
        // Do something with tz_names if necessary
    }

    // Free the timezone
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

    LLVMFuzzerTestOneInput_992(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
