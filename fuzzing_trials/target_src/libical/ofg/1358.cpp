#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t

extern "C" {
    #include <libical/icaltimezone.h>
}

extern "C" int LLVMFuzzerTestOneInput_1358(const uint8_t *data, size_t size) {
    // Ensure that the data is not null and has a valid size
    if (data == nullptr || size == 0) {
        return 0;
    }

    // Call the function-under-test
    bool result = icaltimezone_get_builtin_tzdata();

    // Return 0 as the fuzzer requires an integer return type
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

    LLVMFuzzerTestOneInput_1358(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
