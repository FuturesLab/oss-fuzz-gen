#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/icaltimezone.h>  // Correct header for icaltimezone functions
}

extern "C" int LLVMFuzzerTestOneInput_74(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;  // Not enough data to extract an int and a string
    }

    // Extract an integer from the data
    int offset = static_cast<int>(data[0]);

    // Create a null-terminated string from the remaining data
    const char *tz_name = reinterpret_cast<const char*>(data + 1);

    // Call the function-under-test
    icaltimezone *timezone = icaltimezone_get_builtin_timezone_from_offset(offset, tz_name);

    // Normally, you would do something with the result here, but for fuzzing,
    // we are just interested in whether it crashes or not.

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

    LLVMFuzzerTestOneInput_74(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
