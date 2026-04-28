#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_211(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size == 0) {
        return 0;
    }

    // Create a dummy icalproperty
    icalproperty *prop = icalproperty_new(ICAL_QUERY_PROPERTY);
    if (prop == NULL) {
        return 0; // Failed to create property
    }

    // Set some non-NULL value to the property to ensure it's initialized
    char *query_value = (char *)malloc(size + 1);
    if (query_value == NULL) {
        icalproperty_free(prop);
        return 0; // Memory allocation failed
    }
    memcpy(query_value, data, size);
    query_value[size] = '\0'; // Null-terminate the string

    icalproperty_set_query(prop, query_value);

    // Call the function-under-test
    const char *result = icalproperty_get_query(prop);

    // Additional testing: check if the property has been set correctly
    if (result != NULL && strcmp(result, query_value) == 0) {
        // Further operations can be done here to increase coverage
        // For example, manipulating the property further
        icalproperty_set_query(prop, "test-query");
        const char *new_result = icalproperty_get_query(prop);

        // Check the new result
        if (new_result != NULL && strcmp(new_result, "test-query") == 0) {
            // Perform additional operations to increase coverage
            icalproperty_set_query(prop, "another-query");
            icalproperty_get_query(prop);
        }
    }

    // Clean up
    icalproperty_free(prop);
    free(query_value);

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

    LLVMFuzzerTestOneInput_211(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
