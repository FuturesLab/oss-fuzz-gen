#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_1274(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated and non-empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the null-terminated string
    char *timezone_name = static_cast<char *>(malloc(size + 1));
    if (timezone_name == nullptr) {
        return 0;
    }

    // Copy the data to the string and null-terminate it
    memcpy(timezone_name, data, size);
    timezone_name[size] = '\0';

    // Call the function-under-test
    icaltimezone *timezone = icaltimezone_get_builtin_timezone(timezone_name);

    // Clean up
    free(timezone_name);

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

    LLVMFuzzerTestOneInput_1274(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
