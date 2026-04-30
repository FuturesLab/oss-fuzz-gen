#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include this header for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_793(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Initialize a dummy icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_POLLWINNER_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Extract an integer from the input data
    int pollwinner_value;
    memcpy(&pollwinner_value, data, sizeof(int));

    // Call the function-under-test
    icalproperty_set_pollwinner(prop, pollwinner_value);

    // Clean up
    icalproperty_free(prop);

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

    LLVMFuzzerTestOneInput_793(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
