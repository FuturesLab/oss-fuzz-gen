#include <stddef.h>
#include <stdint.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h> // Correct include path for libical
}

extern "C" int LLVMFuzzerTestOneInput_365(const uint8_t *data, size_t size) {
    // Initialize variables
    icalproperty *property = icalproperty_new(ICAL_EXRULE_PROPERTY);
    struct icalrecurrencetype recurrence;

    // Ensure the data is large enough to fill the icalrecurrencetype structure
    if (size < sizeof(struct icalrecurrencetype)) {
        icalproperty_free(property);
        return 0;
    }

    // Copy data into the icalrecurrencetype structure
    memcpy(&recurrence, data, sizeof(struct icalrecurrencetype));

    // Call the function under test
    icalproperty_set_exrule(property, &recurrence);

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

    LLVMFuzzerTestOneInput_365(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
