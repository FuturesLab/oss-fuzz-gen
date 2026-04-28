#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

// Ensure C linkage for the function-under-test
extern "C" {
    const char *icaltimezone_get_display_name(icaltimezone *);
}

extern "C" int LLVMFuzzerTestOneInput_199(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to create a valid timezone identifier
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *tzid = (char *)malloc(size + 1);
    if (tzid == NULL) {
        return 0;
    }
    memcpy(tzid, data, size);
    tzid[size] = '\0';

    // Initialize a timezone object using the input data as the timezone identifier
    icaltimezone *timezone = icaltimezone_get_builtin_timezone(tzid);

    // Free the temporary tzid string
    free(tzid);

    // Ensure that the timezone object is not NULL
    if (timezone == NULL) {
        return 0;
    }

    // Call the function-under-test
    const char *display_name = icaltimezone_get_display_name(timezone);

    // Optionally, you can print the display name for debugging purposes
    // Note: In a real fuzzing environment, avoid using printf or similar functions
    // printf("Display Name: %s\n", display_name);

    // No need to free the timezone object as it's a built-in timezone

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

    LLVMFuzzerTestOneInput_199(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
