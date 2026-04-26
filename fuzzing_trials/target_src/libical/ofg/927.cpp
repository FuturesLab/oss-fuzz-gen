#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_927(const uint8_t *data, size_t size) {
    // Ensure data is null-terminated for string operations
    char *location_type = (char *)malloc(size + 1);
    if (location_type == NULL) {
        return 0;
    }
    memcpy(location_type, data, size);
    location_type[size] = '\0';

    // Create a new icalproperty object
    icalproperty *property = icalproperty_new(ICAL_ANY_PROPERTY);
    if (property == NULL) {
        free(location_type);
        return 0;
    }

    // Call the function-under-test
    icalproperty_set_locationtype(property, location_type);

    // Clean up
    icalproperty_free(property);
    free(location_type);

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

    LLVMFuzzerTestOneInput_927(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
