#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_298(const uint8_t *data, size_t size) {
    // Ensure data is null-terminated for safe string operations
    if (size == 0) {
        return 0; // No input to process
    }

    char *owner = (char *)malloc(size + 1);
    if (owner == NULL) {
        return 0;
    }

    memcpy(owner, data, size);
    owner[size] = '\0';

    // Call the function-under-test
    icalproperty *property = icalproperty_new_owner(owner);

    // Check if the property was created successfully
    if (property != NULL) {
        // Perform additional operations to increase coverage
        icalproperty_kind kind = icalproperty_isa(property);
        if (kind != ICAL_NO_PROPERTY) {
            // Further operations to explore more code paths
            const char *owner_value = icalproperty_get_owner(property);
            if (owner_value != NULL) {
                // Simulate some property manipulation
                icalproperty_set_owner(property, "new_owner@example.com");
                
                // Additional operations to increase coverage
                icalproperty_set_owner(property, "another_owner@example.com");
                const char *new_owner_value = icalproperty_get_owner(property);
                if (new_owner_value != NULL) {
                    // Further operations can be added here
                }

                // Attempt to set invalid values to explore error paths
                icalproperty_set_owner(property, NULL);
                icalproperty_set_owner(property, "");
            }
        }

        // Clean up
        icalproperty_free(property);
    }

    free(owner);

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

    LLVMFuzzerTestOneInput_298(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
