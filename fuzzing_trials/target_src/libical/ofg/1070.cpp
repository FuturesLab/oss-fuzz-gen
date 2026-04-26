#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1070(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a valid string
    if (size < 1) {
        return 0;
    }

    // Allocate memory for the string and ensure it is null-terminated
    char *tzidaliasof = (char *)malloc(size + 1);
    if (tzidaliasof == NULL) {
        return 0;
    }
    memcpy(tzidaliasof, data, size);
    tzidaliasof[size] = '\0';

    // Create a new icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_TZIDALIASOF_PROPERTY);
    if (prop == NULL) {
        free(tzidaliasof);
        return 0;
    }

    // Call the function under test
    icalproperty_set_tzidaliasof(prop, tzidaliasof);

    // Additional checks to ensure the property was set correctly
    const char *retrieved_tzidaliasof = icalproperty_get_tzidaliasof(prop);
    if (retrieved_tzidaliasof != NULL && strcmp(retrieved_tzidaliasof, tzidaliasof) != 0) {
        // If the retrieved value does not match the set value, there is an issue
        icalproperty_free(prop);
        free(tzidaliasof);
        return 0;
    }

    // Clean up
    icalproperty_free(prop);
    free(tzidaliasof);

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

    LLVMFuzzerTestOneInput_1070(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
