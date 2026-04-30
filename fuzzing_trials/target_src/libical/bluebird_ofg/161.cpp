#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include the header for memcpy

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_161(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to fill the icalrecurrencetype structure
    if (size < sizeof(struct icalrecurrencetype)) {
        return 0;
    }

    // Initialize an icalrecurrencetype structure
    struct icalrecurrencetype recurrence;
    memcpy(&recurrence, data, sizeof(struct icalrecurrencetype));

    // Call the function-under-test
    icalproperty *property = icalproperty_vanew_exrule(&recurrence, NULL);

    // Clean up if the function returns a non-null pointer
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

    LLVMFuzzerTestOneInput_161(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
