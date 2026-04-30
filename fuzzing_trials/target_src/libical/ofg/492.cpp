#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_492(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the query string and ensure it is null-terminated
    char *query = (char *)malloc(size + 1);
    if (query == NULL) {
        return 0;
    }
    memcpy(query, data, size);
    query[size] = '\0';

    // Create a new icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_QUERY_PROPERTY);
    if (prop == NULL) {
        free(query);
        return 0;
    }

    // Call the function-under-test
    icalproperty_set_query(prop, query);

    // Additional invocation of related functions to increase code coverage
    const char *retrieved_query = icalproperty_get_query(prop);
    if (retrieved_query != NULL) {
        // Perform some operation to ensure the query is being used
        icalproperty_set_query(prop, retrieved_query);
    }

    // Check if the property is valid to further increase code coverage
    icalproperty_kind kind = icalproperty_isa(prop);
    if (kind == ICAL_QUERY_PROPERTY) {
        // Perform operations related to the property kind
        const char *kind_str = icalproperty_kind_to_string(kind);
        if (kind_str != NULL) {
            // Use the kind_str to ensure it's being utilized
            icalproperty_set_comment(prop, kind_str);
        }
    }

    // Clean up
    icalproperty_free(prop);
    free(query);

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

    LLVMFuzzerTestOneInput_492(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
