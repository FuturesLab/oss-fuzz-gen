#include <cstdint> // Include for uint8_t
#include <cstddef> // Include for size_t

extern "C" {
    #include <libical/icaltimezone.h>
}

extern "C" int LLVMFuzzerTestOneInput_147(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icaltimezone *timezone = icaltimezone_new();

    // Perform any necessary operations on the timezone object
    // In this case, we don't have any specific operations to perform

    // Free the allocated timezone object to prevent memory leaks
    if (timezone != NULL) {
        icaltimezone_free(timezone, 1);
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

    LLVMFuzzerTestOneInput_147(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
