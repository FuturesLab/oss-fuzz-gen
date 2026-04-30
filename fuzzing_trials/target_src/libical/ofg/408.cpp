#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_408(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for splitting into two strings
    if (size < 2) {
        return 0;
    }

    // Allocate memory for the icalproperty
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Split the input data into two parts for the two string parameters
    size_t split_point = size / 2;

    // Create null-terminated strings from the input data
    char *value = (char *)malloc(split_point + 1);
    char *kind = (char *)malloc(size - split_point + 1);

    if (value == NULL || kind == NULL) {
        icalproperty_free(prop);
        free(value);
        free(kind);
        return 0;
    }

    memcpy(value, data, split_point);
    value[split_point] = '\0';

    memcpy(kind, data + split_point, size - split_point);
    kind[size - split_point] = '\0';

    // Call the function under test
    icalproperty_set_value_from_string(prop, value, kind);

    // Clean up
    icalproperty_free(prop);
    free(value);
    free(kind);

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

    LLVMFuzzerTestOneInput_408(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
