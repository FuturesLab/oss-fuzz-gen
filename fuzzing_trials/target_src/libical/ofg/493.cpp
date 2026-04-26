#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Wrap the C headers and functions in extern "C"
extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_493(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for creating a non-null string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *query = (char *)malloc(size + 1);
    if (query == NULL) {
        return 0;
    }
    memcpy(query, data, size);
    query[size] = '\0';

    // Create an icalproperty instance
    icalproperty *prop = icalproperty_new(ICAL_QUERY_PROPERTY);
    if (prop == NULL) {
        free(query);
        return 0;
    }

    // Call the function under test
    icalproperty_set_query(prop, query);

    // Additional operations to ensure code coverage
    // Retrieve the query to ensure it was set correctly
    const char *retrieved_query = icalproperty_get_query(prop);
    if (retrieved_query != NULL) {
        // Perform some operations to simulate usage
        size_t retrieved_length = strlen(retrieved_query);
        if (retrieved_length > 0) {
            // Simulate some processing
            volatile char first_char = retrieved_query[0];
            (void)first_char;
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

    LLVMFuzzerTestOneInput_493(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
