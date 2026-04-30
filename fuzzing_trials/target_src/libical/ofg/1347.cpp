#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/icalerror.h>
}

extern "C" int LLVMFuzzerTestOneInput_1347(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0; // Ensure there's at least one byte to read
    }

    // Initialize the icalerrorenum with the first byte of data
    icalerrorenum error_enum = static_cast<icalerrorenum>(data[0]);

    // Call the function-under-test
    icalerrorstate state = icalerror_get_error_state(error_enum);

    // Use the state variable to prevent compiler optimizations
    (void)state;

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

    LLVMFuzzerTestOneInput_1347(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
