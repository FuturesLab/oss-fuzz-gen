#include <cstdint>
#include <cstddef>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_656(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract a non-zero length string
    if (size < 2) {
        return 0;
    }

    // Extract an integer from the data
    int kind = static_cast<int>(data[0]);

    // Use the rest of the data as a string
    const char *str = reinterpret_cast<const char*>(data + 1);

    // Call the function-under-test
    int result = icalproperty_kind_and_string_to_enum(kind, str);

    // Use the result in some way to avoid compiler optimizations
    (void)result;

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

    LLVMFuzzerTestOneInput_656(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
