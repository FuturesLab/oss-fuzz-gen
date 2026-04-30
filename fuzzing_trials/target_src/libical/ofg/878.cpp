#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_878(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a valid string for timezone initialization
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char timezone_id[size + 1];
    for (size_t i = 0; i < size; ++i) {
        timezone_id[i] = data[i] % 128; // Ensure valid ASCII characters
    }
    timezone_id[size] = '\0';

    // Initialize a timezone using the string
    icaltimezone *timezone = icaltimezone_get_builtin_timezone(timezone_id);
    if (timezone == NULL) {
        return 0;
    }

    // Call the function-under-test
    icaltimezone *copied_timezone = icaltimezone_copy(timezone);

    // Clean up
    if (copied_timezone != NULL) {
        icaltimezone_free(copied_timezone, 1);
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

    LLVMFuzzerTestOneInput_878(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
