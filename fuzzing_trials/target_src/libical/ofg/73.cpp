#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/icaltimezone.h>
}

extern "C" int LLVMFuzzerTestOneInput_73(const uint8_t *data, size_t size) {
    // Ensure the size is at least enough to extract an int and a char*
    if (size < sizeof(int) + 1) {
        return 0;
    }

    // Extract an integer for the offset
    int offset = *(reinterpret_cast<const int*>(data));

    // Extract a string for the timezone name
    const char* timezone_name = reinterpret_cast<const char*>(data + sizeof(int));

    // Ensure the string is null-terminated within the provided data
    size_t max_str_len = size - sizeof(int);
    size_t str_len = 0;
    while (str_len < max_str_len && timezone_name[str_len] != '\0') {
        str_len++;
    }

    // If the string was not null-terminated, return as it's invalid input
    if (str_len == max_str_len) {
        return 0;
    }

    // Call the function-under-test
    icaltimezone *timezone = icaltimezone_get_builtin_timezone_from_offset(offset, timezone_name);

    // Normally, you would do something with the result, but for fuzzing, we just ensure it runs
    // and doesn't crash. Cleanup if necessary.
    // Note: icaltimezone_get_builtin_timezone_from_offset does not require cleanup of the returned pointer.

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

    LLVMFuzzerTestOneInput_73(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
