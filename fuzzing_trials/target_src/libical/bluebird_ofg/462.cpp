#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_462(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a valid icalproperty object
    if (size < 1) {
        return 0;
    }

    // Create an icalproperty object from the input data
    // For the purpose of this example, let's assume the data represents a string
    // that can be converted into an icalproperty.
    char *ical_string = (char *)malloc(size + 1);
    if (ical_string == NULL) {
        return 0;
    }
    memcpy(ical_string, data, size);
    ical_string[size] = '\0';

    // Parse the string to create an icalproperty
    icalproperty *prop = icalproperty_new_from_string(ical_string);
    free(ical_string);

    // If the property creation failed, return
    if (prop == NULL) {
        return 0;
    }

    // Call the function-under-test
    int max_component_size = icalproperty_get_maxcomponentsize(prop);

    // Clean up
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

    LLVMFuzzerTestOneInput_462(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
