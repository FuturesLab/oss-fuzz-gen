#include <cstddef>
#include <cstdint>
#include <cstring> // For memcpy

extern "C" {
    #include <libical/ical.h> // Correct header for libical project
}

extern "C" int LLVMFuzzerTestOneInput_450(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *zone_id = new char[size + 1];
    memcpy(zone_id, data, size);
    zone_id[size] = '\0';

    // Create an icaltimezone object using the string
    icaltimezone *timezone = icaltimezone_get_builtin_timezone(zone_id);

    // Call the function-under-test
    const char *location = icaltimezone_get_location(timezone);

    // Clean up
    delete[] zone_id;

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

    LLVMFuzzerTestOneInput_450(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
