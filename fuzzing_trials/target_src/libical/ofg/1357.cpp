#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

extern "C" {
    // Declare the function-under-test
    bool icaltimezone_get_builtin_tzdata(const uint8_t *data, size_t size);
}

extern "C" int LLVMFuzzerTestOneInput_1357(const uint8_t *data, size_t size) {
    // Check if size is greater than 0 to ensure data is not null
    if (size > 0) {
        // Call the function-under-test with the provided data
        bool result = icaltimezone_get_builtin_tzdata(data, size);

        // Use the result in some way to avoid compiler optimizations
        if (result) {
            // Do something if the function returns true
        } else {
            // Do something if the function returns false
        }
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

    LLVMFuzzerTestOneInput_1357(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
