#include <cstdint>
#include <cstdlib>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_494(const uint8_t *data, size_t size) {
    // Ensure the data size is at least the size of an icalerrorenum
    if (size < sizeof(int)) {
        return 0;
    }

    // Interpret the input data as an icalerrorenum
    int error_enum_value = 0;
    for (size_t i = 0; i < sizeof(int) && i < size; ++i) {
        error_enum_value |= (data[i] << (i * 8));
    }

    // Cast the interpreted value to icalerrorenum
    icalerrorenum error_enum = static_cast<icalerrorenum>(error_enum_value);

    // Call the function-under-test
    const char *error_str = icalerror_strerror(error_enum);

    // Use the error_str in some way to prevent it from being optimized out
    if (error_str != nullptr) {
        volatile char first_char = error_str[0];
        (void)first_char;
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

    LLVMFuzzerTestOneInput_494(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
