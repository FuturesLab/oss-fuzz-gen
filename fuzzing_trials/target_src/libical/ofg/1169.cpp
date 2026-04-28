#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include the header for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1169(const uint8_t *data, size_t size) {
    // Ensure there is enough data to populate an icaltimetype structure
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Extract an icaltimetype from the input data
    struct icaltimetype time;
    memcpy(&time, data, sizeof(struct icaltimetype));

    // Call the function-under-test
    icalproperty *property = icalproperty_new_recurrenceid(time);

    // Clean up if necessary
    if (property != NULL) {
        icalproperty_free(property);
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

    LLVMFuzzerTestOneInput_1169(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
