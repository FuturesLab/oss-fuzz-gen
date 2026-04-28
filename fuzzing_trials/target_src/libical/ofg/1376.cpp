#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

extern "C" {
    #include <libical/icalerror.h>
}

extern "C" int LLVMFuzzerTestOneInput_1376(const uint8_t *data, size_t size) {
    // Since the function icalerror_get_errors_are_fatal() does not take any parameters,
    // we don't need to use 'data' or 'size' for input. We can directly call the function.

    // Call the function-under-test
    bool result = icalerror_get_errors_are_fatal();

    // Use the result in some way to avoid compiler optimizations
    // that might remove the call if the result is unused.
    // Here, we simply check the result and do nothing with it.
    if (result) {
        // Do nothing
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

    LLVMFuzzerTestOneInput_1376(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
