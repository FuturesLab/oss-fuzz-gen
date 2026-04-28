#include <cstdint>  // For uint8_t
#include <cstdlib>  // For malloc and free
#include <cstring>  // For memcpy

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_942(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated for string operations
    if (size == 0) {
        return 0;
    }

    char *resources = (char *)malloc(size + 1);
    if (resources == NULL) {
        return 0;
    }
    memcpy(resources, data, size);
    resources[size] = '\0';

    // Create a variety of icalproperty types to increase code coverage
    icalproperty *property = icalproperty_new(ICAL_RESOURCES_PROPERTY);
    if (property != NULL) {
        // Call the function under test
        icalproperty_set_resources(property, resources);

        // Additional operations to increase code coverage
        const char *retrieved_resources = icalproperty_get_resources(property);
        if (retrieved_resources != NULL && strcmp(retrieved_resources, resources) == 0) {
            // Successfully set and retrieved the resources
            // Perform additional operations if needed
            // For example, modify the resources and set it again
            resources[0] = 'X';  // Modify the resources
            icalproperty_set_resources(property, resources);
            const char *modified_resources = icalproperty_get_resources(property);
            if (modified_resources != NULL && strcmp(modified_resources, resources) == 0) {
                // Successfully modified and retrieved the resources
            }
        }

        // Clean up
        icalproperty_free(property);
    }

    free(resources);

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

    LLVMFuzzerTestOneInput_942(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
