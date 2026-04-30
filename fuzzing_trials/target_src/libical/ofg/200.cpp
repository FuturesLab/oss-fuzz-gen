#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_200(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char timezone_id[size + 1];
    for (size_t i = 0; i < size; i++) {
        timezone_id[i] = data[i] % 128; // Ensure valid ASCII characters
    }
    timezone_id[size] = '\0';

    // Initialize an icaltimezone object
    icaltimezone *timezone = icaltimezone_get_builtin_timezone(timezone_id);

    // Call the function-under-test
    const char *display_name = icaltimezone_get_display_name(timezone);

    // Use the result to prevent compiler optimizations from removing the call
    if (display_name) {
        // Optionally print or log the display name for debugging purposes
        // printf("Display Name: %s\n", display_name);
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

    LLVMFuzzerTestOneInput_200(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
