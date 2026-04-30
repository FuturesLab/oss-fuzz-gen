#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/icalduration.h> // Include the correct header for icaldurationtype_from_seconds

    // Function-under-test declaration
    struct icaldurationtype icaldurationtype_from_seconds(int);
}

extern "C" int LLVMFuzzerTestOneInput_1029(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create an int
    if (size < sizeof(int)) {
        return 0;
    }

    // Interpret the first bytes of data as an int
    int seconds = 0;
    for (size_t i = 0; i < sizeof(int); ++i) {
        seconds |= (data[i] << (i * 8));
    }

    // Call the function-under-test
    struct icaldurationtype duration = icaldurationtype_from_seconds(seconds);

    // Use the result in some way to avoid compiler optimizations
    // that might remove the call to the function-under-test
    (void)duration;

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

    LLVMFuzzerTestOneInput_1029(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
