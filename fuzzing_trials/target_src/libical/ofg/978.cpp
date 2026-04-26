#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Wrap the C headers and functions in extern "C" to ensure proper linkage
extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_978(const uint8_t *data, size_t size) {
    // Ensure the data is not empty and can be used as a string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the description string and ensure it's null-terminated
    char *description = (char *)malloc(size + 1);
    if (description == NULL) {
        return 0;
    }
    memcpy(description, data, size);
    description[size] = '\0';

    // Create a new icalproperty instance
    icalproperty *prop = icalproperty_new(ICAL_DESCRIPTION_PROPERTY);
    if (prop == NULL) {
        free(description);
        return 0;
    }

    // Call the function-under-test
    icalproperty_set_description(prop, description);

    // Clean up
    icalproperty_free(prop);
    free(description);

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

    LLVMFuzzerTestOneInput_978(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
