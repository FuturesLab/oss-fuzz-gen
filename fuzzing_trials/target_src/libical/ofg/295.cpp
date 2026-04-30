#include <cstdint>  // Include for uint8_t
#include <cstddef>  // Include for size_t

extern "C" {
    #include <libical/icalarray.h>
    #include <libical/icaltimezone.h>  // Include for icaltimezone_array_new
}

extern "C" int LLVMFuzzerTestOneInput_295(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalarray *array = icaltimezone_array_new();

    // Clean up
    if (array != NULL) {
        icalarray_free(array);
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

    LLVMFuzzerTestOneInput_295(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
