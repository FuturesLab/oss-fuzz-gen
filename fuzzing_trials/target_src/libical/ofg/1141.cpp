#include <libical/ical.h>
#include <cstdint>
#include <cstring>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_1141(const uint8_t *data, size_t size) {
    // Ensure the input size is reasonable
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the null-terminated string
    char *tzid = (char *)malloc(size + 1);
    if (tzid == NULL) {
        return 0; // Memory allocation failed
    }

    // Copy the data to the tzid and null-terminate it
    memcpy(tzid, data, size);
    tzid[size] = '\0';

    // Call the function-under-test
    icaltimezone *timezone = icaltimezone_get_builtin_timezone_from_tzid(tzid);

    // Clean up
    free(tzid);

    // The function returns a pointer, but we do not need to do anything with it for fuzzing
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

    LLVMFuzzerTestOneInput_1141(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
