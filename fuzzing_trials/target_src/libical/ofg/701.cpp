#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include the necessary header for memcpy

extern "C" {
    // Include necessary C headers and functions from the libical project
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_701(const uint8_t *data, size_t size) {
    if (size < sizeof(struct icalrecurrencetype)) {
        return 0;  // Not enough data to fill an icalrecurrencetype structure
    }

    // Initialize an icalrecurrencetype structure with data from the fuzz input
    struct icalrecurrencetype recur;
    memcpy(&recur, data, sizeof(struct icalrecurrencetype));

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_exrule(&recur);

    // Clean up
    if (prop != NULL) {
        icalproperty_free(prop);
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

    LLVMFuzzerTestOneInput_701(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
