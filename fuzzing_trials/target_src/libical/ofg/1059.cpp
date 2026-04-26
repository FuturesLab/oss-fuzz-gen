#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include this for memcpy

extern "C" {
    #include <libical/ical.h> // Correctly include the ical library headers
}

extern "C" int LLVMFuzzerTestOneInput_1059(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for a null-terminated string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *tzid = new char[size + 1];
    memcpy(tzid, data, size);
    tzid[size] = '\0';

    // Create a dummy icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);

    // Call the function-under-test
    icalproperty_set_defaulttzid(prop, tzid);

    // Clean up
    icalproperty_free(prop);
    delete[] tzid;

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

    LLVMFuzzerTestOneInput_1059(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
