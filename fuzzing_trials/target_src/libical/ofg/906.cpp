#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

extern "C" {
    #include <libical/icalproperty.h>
}

extern "C" int LLVMFuzzerTestOneInput_906(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for a null-terminated string
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *query_id = (char *)malloc(size + 1);
    if (query_id == NULL) {
        return 0;
    }
    memcpy(query_id, data, size);
    query_id[size] = '\0';

    // Call the function-under-test
    icalproperty *property = icalproperty_vanew_queryid(query_id, NULL);

    // Additional operations to increase code coverage
    if (property != NULL) {
        // Perform operations on the property to ensure it is exercised
        const char *retrieved_id = icalproperty_get_queryid(property);
        if (retrieved_id != NULL) {
            // Compare the retrieved ID with the original to simulate some processing
            if (strcmp(retrieved_id, query_id) == 0) {
                // Do something if they match (this is just an example)
            }
        }
        icalproperty_free(property);
    }

    free(query_id);

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

    LLVMFuzzerTestOneInput_906(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
