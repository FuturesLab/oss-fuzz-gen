#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_102(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a null-terminated string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_TZID_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *tzid = (char *)malloc(size + 1);
    if (tzid == NULL) {
        icalproperty_free(prop);
        return 0;
    }
    memcpy(tzid, data, size);
    tzid[size] = '\0';

    // Call the function-under-test
    icalproperty_set_tzid(prop, tzid);

    // Clean up
    free(tzid);
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

    LLVMFuzzerTestOneInput_102(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
