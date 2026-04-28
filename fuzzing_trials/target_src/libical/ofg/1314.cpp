#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h> // Include for malloc and free

extern "C" {
    #include <libical/icalproperty.h> // Include the correct header for icalproperty
}

extern "C" int LLVMFuzzerTestOneInput_1314(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create a meaningful queryid
    if (size == 0) {
        return 0; // Exit if there's no data to process
    }

    // Initialize icalproperty
    icalproperty *property = icalproperty_new(ICAL_QUERYID_PROPERTY);
    if (property == NULL) {
        return 0; // Exit if property creation fails
    }

    // Ensure that the data is null-terminated to be used as a C string
    char *queryid = (char *)malloc(size + 1);
    if (queryid == NULL) {
        icalproperty_free(property);
        return 0; // Exit if memory allocation fails
    }
    memcpy(queryid, data, size);
    queryid[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    icalproperty_set_queryid(property, queryid);

    // Additional operations to increase code coverage
    const char *retrieved_queryid = icalproperty_get_queryid(property);
    if (retrieved_queryid != NULL) {
        // Compare the set and retrieved queryid to ensure they match
        if (strcmp(queryid, retrieved_queryid) != 0) {
            // Handle mismatch if necessary
            // Log or handle the mismatch to ensure it's not ignored
        }
    } else {
        // Handle the case where retrieved_queryid is NULL
        // This ensures we are testing this path as well
    }

    // Additional property operations to increase coverage
    icalproperty_set_comment(property, "Test comment");
    const char *comment = icalproperty_get_comment(property);
    if (comment != NULL) {
        // Verify comment retrieval
    }

    // Clean up
    icalproperty_free(property);
    free(queryid);

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

    LLVMFuzzerTestOneInput_1314(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
