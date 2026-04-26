#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_474(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to create a null-terminated string
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *queryName = (char *)malloc(size + 1);
    if (queryName == NULL) {
        return 0;
    }
    memcpy(queryName, data, size);
    queryName[size] = '\0';

    // Initialize an icalproperty object with a specific property kind
    icalproperty *property = icalproperty_new(ICAL_QUERYNAME_PROPERTY);
    if (property == NULL) {
        free(queryName);
        return 0;
    }

    // Call the function-under-test
    icalproperty_set_queryname(property, queryName);

    // Add additional operations to increase code coverage
    const char *retrievedQueryName = icalproperty_get_queryname(property);
    if (retrievedQueryName != NULL) {
        // Perform some operation with the retrieved query name
        // For example, compare it with the original to ensure correctness
        if (strcmp(retrievedQueryName, queryName) != 0) {
            // Handle the case where the names do not match
        }
    }

    // Additional fuzzing operations to increase code coverage
    // Attempt to parse the queryName as an icalcomponent
    icalcomponent *component = icalparser_parse_string(queryName);
    if (component != NULL) {
        // Perform operations on the parsed component
        icalcomponent_free(component);
    }

    // Clean up
    icalproperty_free(property);
    free(queryName);

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

    LLVMFuzzerTestOneInput_474(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
