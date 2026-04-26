#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" {
    // Include necessary C headers and function declarations here.
    void icalproperty_set_maxresults(icalproperty *, int);
}

extern "C" int LLVMFuzzerTestOneInput_334(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient to extract an integer value
    if (size < sizeof(int)) {
        return 0;
    }

    // Initialize an icalproperty object
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Extract an integer from the data
    int maxresults = *((int*)data);

    // Call the function-under-test
    icalproperty_set_maxresults(property, maxresults);

    // Clean up
    icalproperty_free(property);

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

    LLVMFuzzerTestOneInput_334(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
