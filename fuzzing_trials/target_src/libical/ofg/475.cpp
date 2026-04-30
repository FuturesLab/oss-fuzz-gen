#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_475(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for a null-terminated string
    if (size < 1) return 0;

    // Create an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);
    if (prop == NULL) return 0;

    // Allocate memory for a null-terminated string
    char *queryname = (char *)malloc(size + 1);
    if (queryname == NULL) {
        icalproperty_free(prop);
        return 0;
    }

    // Copy data into queryname and null-terminate it
    memcpy(queryname, data, size);
    queryname[size] = '\0';

    // Call the function under test
    icalproperty_set_queryname(prop, queryname);

    // Clean up
    free(queryname);
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

    LLVMFuzzerTestOneInput_475(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
