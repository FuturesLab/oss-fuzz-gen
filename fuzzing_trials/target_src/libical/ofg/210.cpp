#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_210(const uint8_t *data, size_t size) {
    // Ensure there's enough data to create a valid icalproperty
    if (size < 1) {
        return 0;
    }

    // Create a dummy icalproperty
    icalproperty *property = icalproperty_new(ICAL_QUERY_PROPERTY);

    if (property == NULL) {
        return 0;
    }

    // Set some value to the property using the input data
    // Convert data to a null-terminated string
    char *value = (char *)malloc(size + 1);
    if (value == NULL) {
        icalproperty_free(property);
        return 0;
    }
    memcpy(value, data, size);
    value[size] = '\0';

    // Assign the value to the property
    icalvalue *ical_val = icalvalue_new_from_string(ICAL_STRING_VALUE, value);
    if (ical_val == NULL) {
        free(value);
        icalproperty_free(property);
        return 0;
    }
    icalproperty_set_value(property, ical_val);

    // Call the function-under-test
    const char *query = icalproperty_get_query(property);

    // Check if query is not NULL to ensure the function under test is being invoked effectively
    if (query != NULL) {
        // Perform some operations with query to ensure code coverage
        size_t query_len = strlen(query);
        if (query_len > 0) {
            // Example operation: print query length
            printf("Query length: %zu\n", query_len);
        }
    }

    // Clean up
    free(value);
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

    LLVMFuzzerTestOneInput_210(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
