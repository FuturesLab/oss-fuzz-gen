#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include the necessary header for memcpy

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_877(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a valid timezone string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *timezone_id = new char[size + 1]; // Use dynamic allocation
    memcpy(timezone_id, data, size);
    timezone_id[size] = '\0';

    // Create a default timezone to ensure the input is not NULL
    icaltimezone *default_timezone = icaltimezone_get_utc_timezone();

    // Attempt to find a timezone using the input data
    icaltimezone *timezone = icaltimezone_get_builtin_timezone(timezone_id);
    if (timezone == NULL) {
        timezone = default_timezone;
    }

    // Call the function-under-test
    icaltimezone *copied_timezone = icaltimezone_copy(timezone);

    // Clean up
    if (copied_timezone != NULL && copied_timezone != default_timezone) {
        icaltimezone_free(copied_timezone, 1);
    }
    delete[] timezone_id; // Free the dynamically allocated memory

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

    LLVMFuzzerTestOneInput_877(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
