#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include for memcpy

extern "C" {
    // Ensure all C headers and functions are wrapped with extern "C"
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_967(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to populate an icalrecurrencetype structure
    if (size < sizeof(struct icalrecurrencetype)) {
        return 0;
    }

    // Initialize an icalrecurrencetype structure from the input data
    struct icalrecurrencetype recurrence;
    memcpy(&recurrence, data, sizeof(struct icalrecurrencetype));

    // Call the function under test
    icalproperty *property = icalproperty_vanew_exrule(&recurrence, NULL);

    // Clean up the created icalproperty if it's not NULL
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

    LLVMFuzzerTestOneInput_967(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
