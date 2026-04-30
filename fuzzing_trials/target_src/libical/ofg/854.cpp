#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>  // Include this header for size_t

// Assuming the function is part of a C library, include it with extern "C"
extern "C" {
    void icalerror_set_errors_are_fatal(bool);
}

extern "C" int LLVMFuzzerTestOneInput_854(const uint8_t *data, size_t size) {
    // Ensure there's at least one byte to read
    if (size < 1) {
        return 0;
    }

    // Use the first byte of data to determine the boolean value
    bool errors_are_fatal = (data[0] % 2 == 0);

    // Call the function-under-test
    icalerror_set_errors_are_fatal(errors_are_fatal);

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

    LLVMFuzzerTestOneInput_854(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
