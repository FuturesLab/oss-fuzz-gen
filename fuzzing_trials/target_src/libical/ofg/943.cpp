#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_943(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a meaningful string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the icalproperty
    icalproperty *property = icalproperty_new(ICAL_RESOURCES_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Copy the data into a null-terminated string
    char *resourceString = (char *)malloc(size + 1);
    if (resourceString == NULL) {
        icalproperty_free(property);
        return 0;
    }
    memcpy(resourceString, data, size);
    resourceString[size] = '\0';

    // Call the function-under-test
    icalproperty_set_resources(property, resourceString);

    // Additional checks to ensure the function is being utilized
    const char *retrievedResource = icalproperty_get_resources(property);
    if (retrievedResource != NULL && strcmp(retrievedResource, resourceString) == 0) {
        // The property was set correctly, indicating the function is being utilized
    }

    // Clean up
    free(resourceString);
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

    LLVMFuzzerTestOneInput_943(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
